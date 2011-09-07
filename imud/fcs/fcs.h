#ifndef IMUD_FCS_H_INCLUDED
#define IMUD_FCS_H_INCLUDED
// by firefox 04/16/2011
// 


#include <imud-efun.h>


#include <ansi.h>

/********************************常量定义***********************************/

#define MAX_CARD				5					//做多牌数量
#define	MIN_PLAYER				2					//最少玩家数
#define	MAX_PLAYER				5					//最多玩家数
#define	PLAYER_TIME				60					//玩家思考时间
#define BAN_TIME				600					//中途退场，禁止报名的时间
#define PULSE					6					//脉搏
#define MIN_CHIP				100					//玩家最少筹码数

/********************************本地化常量***********************************/

#define ROE						(200*10000/1000)	//汇率，日收入换1K筹码
#define DEALER_NAME				"发牌女郎"			//

/********************************对象***********************************/

#define FAMILY_SKILLS			__DIR__"family-skill"




/********************************数据定义***********************************/

mapping _g;						//全局数据
object_f _localizer;			//本地化对象
mapping _dealer;				//发牌者
int _game_id;					//当前游戏id
object_f _stand;				//看台

/********************************函数定义***********************************/


//获取玩家数据
varargs mixed data_of(object who, string prop)
{
	string root = _localizer->get("prop_root");
	mapping m = who->query(root);
	if(!mapp(m)) who->set(root, m = ([]));
	return prop ? m[prop] : m;
}

//初始化
void fcs_init()
{
	_g = ([
		"queue"			: ({}),				//排队玩家信息
		"players"		: ({}),				//玩家信息(mid, name, id, chip, state, no., bet)

		"round"			: 0,				//第几轮
		"turn"			: -1,				//当前玩家序号
		"timeout"		: 0,				//当前玩家是否超时
		"pot"			: 0,				//池底筹码数
		"bet"			: 0,				//当前赌注
		"max_bet"		: 0,				//本轮下注上限
		"cards"			: allocate(7*4),	//牌
	]);

	_localizer	= __DIR__"localizer";
	_dealer		= ([]) + _localizer->get("dealer");
	_game_id	= path_file(__FILE__)[0] - '0';
	_stand		= __DIR__"stand" + _game_id;
}

mixed g()
{
	return _g;
}

//玩家数
int players_number()
{
	return sizeof(_g["players"]);
}




//离场
int leave(string arg)
{

}


//某人就绪
int sb_ready(string gid)
{
}



//跟注
int call(string arg)
{
}

//加注
int raise(string arg)
{}




//计算赢家
void calc_winner()
{
}
/********************************下注顺序***********************************/



//轮到当前
mapping turn_who()
{
	int n = _g["turn"];
	foreach(mapping who in _g["players"]) {
		if(who["no."] == n) return who;
	}
	return 0;
}

//比较玩家本轮牌大小
int turn_cmp(int a, int b)
{
	int n = _g["round"];
	return _g["players"][b]["cards"][n] - _g["players"][a]["cards"][n];
}

//初始化新一轮，计算下注顺序
void turn_init()
{
	int n = players_number();
	int* arr = allocate(n);
	
	for(int i = 0; i < n; ++i) {
		_g["players"][i]["bet"] = 0;
		arr[i] = i;
	}
	arr = sort_array(arr, (: turn_cmp :));
	for(int i = 0; i < n; ++i) {
		_g["players"][arr[i]]["no."] = i;
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
mapping find_info(object who, mixed* arr)
{
	string id = getuid(who);

	foreach(mapping m in arr) {
		if(m["mid"] == MUD_ID && m["id"] == id) return m;
	}
	return 0;
}

//获得玩家信息
mapping this_info()
{	
	return find_info(this_player(), _g["players"]);
}




//显示一组牌
void show_cards(int* cards);


//显示信息
varargs int msv1(string msg, mapping me, mapping target, mixed arg);


#endif

