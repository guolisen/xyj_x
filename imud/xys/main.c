// by firefox 10/01/2010
// 西游杀-战斗主循环

#include "xys.h"
#include "family.c"
#include "card-role.c"
#include "card-weapon.c"

mapping _win_msg = ([
	VIP	+ ZHONG		: "传闻$N梦境中化身取经人，带领徒弟降妖除魔一路西行。",
	ZHONG			: "传闻$N梦境中护送取经人，降妖除魔一路西行。",
	JIAN			: "传闻$N梦境中扮作取经人徒弟，强夺通关文牒，踏上取经路。",
	FAN				: "传闻$N梦境中化身妖魔捉了取经人蒸吃了。",
]);	



object _room;				//

int char_stage;				//玩家所处阶段



/********************************私有变量***********************************/
int	_status	= DONE;

int _char_tick = 0;			//玩家计时


/********************************开始阶段***********************************/

//玩家加入
int join(string id, int role)
{
	object who = find_player(id);
	mixed* cards = allocate(CARDS_SIZE);
	string family = family_of_random();

	HP->full(who);
	who->move(_this);
	tell_object(who, YEL"朦胧中，你来到了另一个世界。\n"NOR);

	_chars[id] = ([
		"id"		: id,
		"name"		: who->query("name"),
		"camp"		: role & 0xff,
		
		"kee"		: 100,
		"sen"		: 100,
		"force"		: 100,
		"mana"		: 100,

		"skills"	: family_skills(family),
		"state"		: allocate(sizeof(_states)),
		"BUFF_PROP"	: ([]),
		"cards"		: cards,
	]);

	cards[0] = _card_roles[role];

	cards[1] = _card_defense;
	cards[2] = family_uskill(family, 0);
	cards[3] = family_uskill(family, 1);
	cards[4] = family_uskill(family, 2);

	cards[5] = _card_unarmed;

	return 1;
}

//玩家离开
int leave(string id)
{
	object who = find_player(id);

	if(who && environment(who) == _this) {
		string bed = or2(who->query("dream_place"), "/d/changan/pinqiting");
		HP->full(who);
		who->move(bed);
		tell_object(who, CYN"\n你揉揉眼睛，醒了过来。\n\n"NOR);		
	}
	
	//XYS->ip_remove_id(id);
}


//邀请玩家入场
int invite_all(string* ids)
{
	if(_status != DONE) return -1;

	_status = BATTLE;
	_start_time = time();

	//随机乱序，然后决定身份
	ids = MATH->shuffle_arr(ids);
	
	join(ids[0], ZHONG + VIP);
	join(ids[1], ZHONG);	
	join(ids[2], JIAN);
	join(ids[3], FAN);
	join(ids[4], FAN);
	join(ids[5], FAN);
	
	//决定vip以外的人的座次
	ids -= ({ ids[0] });
	ids = MATH->shuffle_arr(ids);

	for(int i = 0; i < sizeof(ids); ++i) {
		_chars[ids[i]]["order"] = i + 1;
	}
	
	//初始发牌
	foreach(string id, mapping m in _chars) {
		for(int i = 0; i < INIT_CARD; ++i) deal(id);
	}	
	return 1;	//等待主攻用start命令启动循环
}

//开始游戏
int start(string* ids)
{
	set_heart_beat(PULSE);
	next_one();
}
/********************************进行阶段***********************************/

//计算胜利方，PANDING - 尚未决出胜负
int calc_winner()
{
	if(is_dead(_chars[_vip_id])) {
		if(count_camp(FAN)) return FAN;				//反贼
		else if(count_camp(ZHONG))return ZHONG;		//忠臣
		return JIAN;								//奸臣
	}
	else if(!count_camp(FAN) && !count_camp(JIAN))
		return ZHONG;								//忠臣
	return 0;
}

//是否有人胜利
int sb_win()
{
	int winner = calc_winner();
	if(winner) {
		done(winner);
		return 1;
	}
	return 0;
}

//刷新状态
void refresh_state(mapping who)
{
	for(int i = 0; i < sizeof(who["state"]); ++i) {
		if(who["state"][i] > 0) who["state"][i]--;
	}
}

//下一个玩家
int next_one()
{
	//查找下一个活人
	_char_tick = 0;
	do {
		_char_no = (_char_no + 1) % sizeof(_chars);
		_char = _chars[_order[_char_no]];
		
	} while(!is_dead(_char));

	//刷新buff,状态
	buff_refresh_all(_char);
	refresh_state();

	//检查胜利条件
	if(win()) return 1;
	
	//如果玩家处于失控状态，则跳过
	if(out_of_control(_char)) return next_one();
	
	deal(_char);	//发牌，等待玩家出牌
	return 1;
}

//计算阵营人数
int camp_count(int camp)
{
	int s = 0;
	foreach(string id, mapping who in _chars) {
		if(who["camp"] == camp && !is_dead(who)) s++;
	}
	return s;
}


//战场的心跳
void heart_beat()
{
	//检查玩家是否已经退出
	foreach(string id, mapping m in _chars) {
		object who = find_player(id);

		//逃兵lamster
		if(!who || environment(who) != _room)
			leave(id);

		m["order"] = -1;
	}

	//检查是否满足结束条件
	if(calc_winner()) stop();

	//提示玩家时间
	_char_tick++;
	if(_char_tick > CHAR_TIME - 3)
		tell_room(_room, "" + _char_tick);

	//超时，下一个人
	if(_char_tick == CHAR_TIME) {
		next_one();
	}
}

/********************************结束阶段***********************************/

//发放奖励，离场
void done(int winner)
{
	int duration = time() - _start_time;
	object* winners = ({});

	_status = DONE;
	set_heart_beat(0);

	foreach(string id, mapping m in _chars) {
		object who = find_player(id);
		if(who) {
			who->add(XYS_PROP + "/duration", duration);
			if(m["camp"] & winner) {
				who->add(XYS_PROP + "/win", 1);
				who->add("balance", REWARD_GOLD*10000);
				winners += ({ who });
			}
		}
	}

	if(winner)
		random1(winners)->co	mmand("rumor " + _win_msg[winner] + "\n");	

	foreach(string id, mapping m in _chars) {
		leave(id);
	}
}

//战斗结束
int stop()
{
	done(calc_winner());
	return 1;
}

/********************************辅助工具***********************************/




//失控状态
int out_of_control()
{

}

//挂了
int is_dead(mapping who)
{
	return 1;
}

//计算活人数
int living_count()
{
	int n = 0;
	foreach(string id, mapping who in _chars) {
		n += is_dead(who);
	}
	return n;
}

//发牌
int deal()
{
	mapping card =([
		"type"		: "角色",
		"name"		: "取经人",
		"comment"	: "被保护与被猎杀的对象",

	]);
	
	//武器
	//装备
	//马匹
	//法宝
	//药物
	
	


}

//记录
void report(object obj, string msg)
{
	//MONITOR_D->report_system_object_msg(obj, msg + "\n");
}


//查找下一个玩家
mapping find_next(mapping who);

//查找前一个玩家
mapping find_prevous(mapping who);

