// by firefox 04/16/2011
// 

#include "msg.h"
#include "util_s.h"
#include "score.c"
#include <imud-efun.h>
#include <ansi.h>

/********************************常量定义***********************************/


#define	MIN_PLAYER				2					//最少玩家数
#define	MAX_PLAYER				5					//最多玩家数
#define	PLAYER_TIME				120					//玩家思考时间
#define BAN_TIME				600					//中途退场，禁止报名的时间
#define PULSE					6					//脉搏
#define MIN_CHIP				100					//玩家最少筹码数


#define PREADY					4					//玩家是否就绪
#define PBET					4					//玩家本轮投注额
#define PNUM					5					//玩家序号
#define PCARDS					6					//玩家的牌


/********************************本地化常量***********************************/

#define ROE						(200*10000/1000)	//汇率，日收入换1K筹码
#define DEALER_NAME				"发牌女郎"			//

/********************************对象***********************************/

#define FAMILY_SKILLS			__DIR__"family-skill"

/********************************数据定义***********************************/

int _game_id;					//当前游戏id


/********************************函数定义***********************************/


int next_one();
void reward_winner(mixed* who);
int start();

/********************************函数定义***********************************/





//初始化
void fcs_init()
{
	_g = ([
		"queue"			: ({}),				//排队玩家信息
		"players"		: ({}),				//玩家信息(name, id, mud, score, bet/ready, num, cards)

		"round"			: 0,				//第几轮
		"turn"			: -1,				//当前玩家序号
		"timeout"		: 0,				//当前玩家是否超时
		"pot"			: 0,				//池底筹码数
		"bet"			: 0,				//当前赌注
		"max_bet"		: 0,				//本轮下注上限
		"cards"			: allocate(7*4),	//牌
	]);

	_game_id	= path_file(__FILE__)[0] - '0';

}

//玩家数
int players_number()
{
	return sizeof(_g["players"]);
}

//游戏开始
int start()
{
	foreach(mixed* u in _g["queue"]) {
		u[UREADY] = 0;
	}
	_g["players"] = _g["queue"];
	_g["queue"] = ({});

	//洗牌
	for(int i = 0; i < sizeof(_g["cards"]); ++i) {
		_g["cards"][i] = i;
	}
	shuffle(_g["cards"]);

	//给玩家牌
	for(int i = 0; i < players_number(); ++i) {
		for(int j = 0; j < MAX_CARD; ++j)
			_g["players"][i][PCARDS][j] = _g["cards"][i*MAX_CARD + j];
	}
	dealing();
	return 1;
}

//强制结束游戏
int stop()
{
	//平分/退还筹码，离场
	int n = _g["pot"] / sizeof(_g["players"]);
	foreach(mixed* who in _g["players"]) {
		who[USCORE] += n;
		send_req("on_leave", who);
	}
}


//展示发牌过程
void dealing()
{
	int min_chip = _g["players"][0][PSCORE];

	_g["round"]++;
	
	dealer_say("开始发牌！\n");													//todo
	for(int i = 0; i < players_number(); ++i) {
		mixed* who = _g["players"][i];
		show_sb_cards(who);
		//call_out("show_sb_cards", PULSE * (i + 1), _g["players"][i]);
		
		if(who[PSCORE] < min_chip) min_chip = who[PSCORE];
	}

	//限制下注
	_g["max_bet"] = min_chip / (MAX_CARD  - _g["round"]);

	//计算下注顺序
	turn_init();
	_g["bet"] = 0;

	next_one();
}

//奖励胜利者
void reward_winner(mixed* who)
{
	who[PSCORE] += _g["pot"];
	_g["pot"] = 0;

	send_req("on_reward_winner");
}

//计算赢家
void finish()
{
	mixed* players = _g["queue"] + _g["players"];

	if(players_number() == 1) {
		reward_winner(_g["players"][0]);
	} else {
		int* max_score = ({-1});
		mixed* winner;
		foreach(mixed* who in _g["players"]) {
			int* score = cards_score(who[PCARDS]);

			show_sb_cards(who, 1);							//todo
			dealer_say(_score_name[score[0]] + "!\n");
			
			if(cmp_score(score, max_score) > 0) {
				max_score = score;
				winner = who;
			}
		}
		reward_winner(winner);
	}	

	fcs_init();	
	_g["queue"] = players;

	refresh_look();
}

//玩家超时
void wait_timeout()
{
	mixed* who = turn_who();

	dealer_say("$N超过规定时间，算作弃牌。\n", who);
	fold(who);
	next_one();
}


//下一个玩家
int next_one()
{
	mixed* who;

	refresh_look();

	for(int i = 0; i < MAX_PLAYER; ++i) {
		_g["turn"] = (_g["turn"] + 1) % MAX_PLAYER;
		who = turn_who();
		if(who) break;
	}
	remove_call_out("wait_timeout");	
	if(players_number() == 1) {
		finish();
	} else if(!_g["bet"] || who[PBET] < _g["bet"]) {	//还未下注或需要跟别人的加注
		
		dealer_say("$N，请下注。\n", who);
		call_out("wait_timeout", PLAYER_TIME);		//todo:
	} 
	else if(_g["round"] < MAX_CARD - 1) {
		dealing();
	} else {
		finish();
	}
	return 1;
}






//计算赢家
void calc_winner()
{
}
/********************************下注顺序***********************************/



//轮到当前
mapping turn_who()
{
	int n = _g["turn"];
	foreach(mixed* who in _g["players"]) {
		if(who[PNUM] == n) return who;
	}
	return 0;
}

//比较玩家本轮牌大小
int turn_cmp(int a, int b)
{
	int n = _g["round"];
	return _g["players"][b][PCARDS][n] - _g["players"][a][PCARDS][n];
}

//初始化新一轮，计算下注顺序
void turn_init()
{
	int n = players_number();
	int* arr = allocate(n);
	
	for(int i = 0; i < n; ++i) {
		_g["players"][i][PBET] = 0;
		arr[i] = i;
	}
	arr = sort_array(arr, (: turn_cmp :));
	for(int i = 0; i < n; ++i) {
		_g["players"][arr[i]][PNUM] = i;
	}
	_g["turn"] = -1;
}
/********************************函数定义***********************************/





//获取该玩家带服务器信息的ID
string gid(object who)
{
	return getuid(who) + "@" + MUD_ID;
}

//查找玩家信息
mixed* find_info(mixed* info, mixed* arr)
{
	foreach(mixed* u in arr) {
		if(u[PMUD] == info[PMUD] && u[PID] == info[PID]) return u;
	}
	return 0;
}


//显示一组牌
void show_cards(int* cards);


//显示信息
varargs int msv1(string msg, mapping me, mapping target, mixed arg);


/********************************状态检查***********************************/

/********************************状态检查***********************************/

#define CHK_FAIL_STARTED			if(_g["round"] > 0) return notify(MSG_STARTED)
#define CHK_FAIL_NOT_START			if(!_g["round"]) return notify(MSG_NOT_START)
#define CHK_FAIL_NOT_YOU(who)		if(turn_who() != (who)) return notify(MSG_NOT_YOU);
#define CHK_OOC(who, cn)			if(who[PSCORE] < (cn)) return notify(MSG_NOT_ENOUGH);

#define CHK_CHIP_TOO_LESS(n)		if((n) < 1) return notify(MSG_AT_LEAST_1);
#define CHK_CHIP_TOO_MUCH(n)		if((n) > _g["max_bet"]) return notify(MSG_TOO_MUCH, _g["max_bet"]);

/********************************准备阶段***********************************/
///玩家加入
int join(mixed* info)
{
	CHK_FAIL_STARTED;
	
	if(sizeof(_g["queue"]) < MAX_PLAYER) {		
		mixed* who = find_info(info, _g["queue"]);
		if(who) return notify(MSG_JOINED);		
		who = ({
			info[PNAME],
			info[PID],
			info[PMUD],
			info[PSCORE],
			0,					//PREADY
			0,					//PNUM
			allocate(MAX_CARD)
		});
		_g["queue"] += ({ who });

		return refresh_all(info);
	}
	return notify(info, MSG_FULL);
}

//入场选手离开
mapping leave(mixed* info)
{
	mixed* who = find_info(info, _g["queue"]);

	CHK_FAIL_STARTED;

	if(!who) notify(MSG_NOT_JOIN);

	_g["queue"] -= ({ who });
	
	return who[PSCORE];
}

//是否可以开始
private int can_start()
{
	//判读可否开始
	if(sizeof( _g["queue"]) < MIN_PLAYER) return 0;
	foreach(mapping m in _g["queue"]) {
		if(!m["ready"]) return 0;
	}
	return 1;
}

//入场选手宣布就绪
mapping ready(mixed* info)
{
	mixed* who = find_info(info, _g["queue"]);
	
	CHK_FAIL_STARTED;
	if(!who) return notify(MSG_NOT_JOIN);
	if(who[PSCORE] < MIN_CHIP) return notify(MSG_TOO_LESS, MIN_CHIP);

	who["ready"] = 1;
	
	if(can_start())	start();
	return msgv(MSG_READY);
}

//买筹码
mapping exchange(mixed* info)
{
	mixed* who = find_info(info, _g["queue"]);
	int n;
	
	CHK_FAIL_STARTED;
	if(!who) return notify(MSG_NOT_JOIN);
	CHK_OOC(who, n);

	who[PSCORE] += n;

	return n;
}


/********************************进行阶段***********************************/

//下注
private int sb_bet(mixed* who, int n)
{
	who[PSCORE] -= n;
	who[PBET] += n;
	_g["pot"] += n;
	if(n > _g["bet"]) _g["bet"] = n;
}

//下注
mapping bet(mixed* info)
{
	mixed* who = find_info(info, _g["players"]);

	int n = to_int(arg);
	
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);	
	if(_g["bet"]) return notify(MSG_BETTED);
	CHK_CHIP_TOO_LESS(n);
	CHK_CHIP_TOO_MUCH(n);
	CHK_OOC(who, n);

	sb_bet(who, n);	
	say(who, n + "!\n");

	return next_one();
}

//跟注
mapping call(mixed* info)
{
	mixed* who = find_info(info, _g["players"]);
	int n;

	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);	
	if(!_g["bet"]) return notify(MSG_PLS_BET);
	n = _g["bet"] - who[PBET];
	CHK_OOC(who, n);

	sb_bet(who, n);
	say(who, "跟了！\n\n");

	return next_one();
}

//加注
mapping raise(mixed* info)
{
	mixed* who = find_info(info, _g["players"]);
	int add = to_int(arg);
	int n = _g["bet"] + add;
	
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);

	if(!_g["bet"]) return notify(MSG_PLS_BET);
	if(who[PBET] > 0) return notify(MSG_CALL_OR_FOLD);
	CHK_CHIP_TOO_LESS(add);
	CHK_CHIP_TOO_MUCH(n);	
	CHK_OOC(who, n);

	sb_bet(who, n);
	say(who, "加" + add + "！\n\n");

	return next_one();
}

//弃牌
mapping fold(mixed* info)
{
	mixed* who = find_info(info, _g["players"]);
		
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);

	if(!_g["pot"]) return notify(MSG_NO_FOLD);

	_g["queue"] += ({ who });
	_g["players"] -= ({ who });
	
	return next_one();
}

