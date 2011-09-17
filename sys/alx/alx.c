// by firefox 11/21/2009
// alx战场

#pragma optimize

inherit F_DBASE;

#include "camp.c"
#include "score.c"
#include "cmds.c"
#include "room_act.c"
#include "helper.c"

#include "alx.h"

/********************************私有变量***********************************/

int _time;									//战斗持续时间

/********************************函数定义***********************************/

int stop();

private void report(object obj, string msg);
private void chat(int camp, string str);

private int on_timer(mapping buff);

/********************************初始化***********************************/

void create()
{
	seteuid(getuid());
	
	_status	= DONE;
	//BUFF->repair_all();		//修理玩家buff
}


/********************************邀请阶段***********************************/

//开始邀请
int start()
{
	if(_status != DONE) return -1;

	destruct(load_object(MAP));

	_status = INVITE;
	chat(XIAN, HIG"除魔卫道，广邀各路神仙协力铲平狮驼岭。");
	chat(MO, HIR"我那山场，非一日治的，恭请三界妖魔助战！");

	remove_call_out("battle_start");
	call_out("battle_start", 2*60);
}

/********************************启动阶段***********************************/

//战斗开始
int battle_start()
{
	if (_status != INVITE) return -1;

	//初始化阵营
	_camps[XIAN] = ([
		"name"		: "仙界",
		"index"		: XIAN,
		"color"		: HIG,
	]);
	_camps[MO] = ([
		"name"		: "魔道",
		"index"		: MO,
		"color"		: HIR,
	]);

	_status = BATTLE;
	_start_time = time();
	_time = 0;
	
	rumor("朵朵祥云飘荡在八百里狮驼岭上空，隆隆战鼓也从山岭间响起。\n");

	help_init();
	camp_init();
	camp_accept_all();

	set_heart_beat(PULSE);
	return 1;
}
/********************************进行阶段***********************************/

//计算胜利方，PANDING - 尚未决出胜负
private int calc_winner(int time)
{
	mapping xian = _camps[XIAN];
	mapping mo = _camps[MO];

	if(xian["res"] >= MAX_RES) return XIAN;		//仙资源满
	if(mo["res"] >= MAX_RES) return MO;			//魔资源满
	if(time() - _start_time >= time) {			//超时
		return xian["res"] > mo["res"] ? XIAN : MO;
	}
	return 0;
}

//治疗玩家
private void cure_user(object user)
{
	if(user->is_busy() || user->fighting() || user->query("env/invisibility")) return;
	user->receive_curing("kee", HP_CURE);
	user->receive_curing("sen", HP_CURE);
}

//遍历阵营玩家
void for_camp(mapping camp)
{	
	camp["users"] -= ({ 0 });
	foreach(object who in camp["users"]) {		
		//拉回离场玩家
		object env = environment(who);
		mapping buff = BUFF->find(who, WAIT4R);	//等待复活的buff
		if(buff || !env || !(env->query("in_bg") || env->query("is_fabao"))) {
			if(!wizardp(who)) room_goto_hell(who);
		}
		//增加玩家移动点数
		score_set(who, "mp", PULSE * 2);
		//治疗玩家
		cure_user(who);
		reset_eval_cost();
	}
}

//战场的心跳
void heart_beat()
{
	_time += PULSE;

	//战斗前期定时搜索请求加入的玩家
	if(_time < ACCEPT_TIME && _time % INVITE_USER == 0)
		camp_accept_all();

	//检查IP
	if(_time % INVITE_USER == PULSE)
		camp_check_ip();
	
	//分发救命毫毛
	if(_time % ALLOT_HAIR == 0) help_allot_hair();

	//计算占领据点奖励
	foreach(object flag in MAP->flags()) {
		int c = camp_id(flag);
		if(c && !BUFF->find(flag, BG_NO_RES))
			_camps[c]["res"] += FLAG_RES * PULSE;
	}
	
	//按奇/偶检查全部玩家
	if(_time / PULSE % 2) for_camp(_camps[XIAN]);
	else for_camp(_camps[MO]);

	//检查是否满足结束条件
	if(calc_winner(MAX_TIME)) stop();
}

/********************************结束阶段***********************************/

//战斗结束
int stop()
{
	int winner = calc_winner(0);
	_status = DONE;
	set_heart_beat(0);

	rumor(TITLE"结束了，" + camp_name(_camps[winner]) + HIM"取得暂时的胜利。\n");
	report(_this, "时间:" + _time + " 胜利:" + winner);
	
	for(int i = 1; i < sizeof(_camps); ++i) {
		mapping camp = _camps[i];
		int res = camp["res"];
		if(i == winner) res += WIN_POT;
		report(_this, "阵营:" + i + " 资源奖励:" + res);
		//分发奖励
		foreach(object user in camp["users"]) {
			int exp = score_query(user, "exp");
			int ratio = 100 * score_liveness(user) / 2;		//活跃点就能拿全奖励
			int total = exp + res * truncate(ratio, 30, 100) / 100;
			total = truncate(total, MIN_TOTAL_POT, MAX_TOTAL_POT);

			score_set(user, "exp", total);
			score_add_total(user);
			score_add(user, "times", 1);
			
			if(interactive(user)) score_add_gold(user, total / K / 3);

			reset_eval_cost();
		}
	}
	{
		//广播成绩 & 退场
		object* users = sort_user("cmp_kill0");
		broadcast_score(users);

		foreach(object who in users) {
			camp_leave(who);
		}
	}
	//清理
	foreach(object flag in MAP->flags()) {
		BUFF->clear(flag);
	}
	return 1;
}

/********************************辅助工具***********************************/

//防止update命令的内存泄漏
int update(string arg)
{
	if(arg == "here") {
		write("战场npc被销毁。\n");
		destruct(_this);
		return 1;
	}
	return 0;
}

//领袖发话
void chat(int camp, string str)
{
	MAP->leaders()[camp]->command("chat " + str);
}

//谣言宣布
void rumor(string str)
{
	MAP->leaders()[1]->command("rumor " + str);
}

//记录
void report(object obj, string msg)
{
	//MONITOR_D->report_system_object_msg(obj, msg + "\n");
}

