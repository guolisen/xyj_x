// by firefox 04/16/2011
// fcs client

#include <imud-efun.h>
#include "fcs.h"

inherit ROOM;
inherit F_iCLIENT;

#include "cards.c"

#define MAX_EXCHANGE			100000				//兑换上限

mixed* _dealer;										//发牌者
mapping _g = (["pot" : 0, "queue" : ({}), "players" : ({})]);

static mapping _msgs = ([

	MSG_STARTED			: "游戏已经开始了。\n",
	MSG_NOT_START		: "游戏还未开始。\n",
	MSG_NOT_YOU			: "还没轮到你。\n",
	MSG_JOINED			: "你已经加入了。\n",
	MSG_NOT_JOIN		: "你没加入游戏。\n",
	MSG_FULL			: "桌边已经坐满了。\n",

	MSG_NOT_ENOUGH		: "你没有足够的筹码。\n",
	MSG_AT_LEAST_1		: "至少要一个筹码。\n",
	MSG_TOO_LESS		: "至少要有%s个筹码。\n",
	MSG_TOO_MUCH		: "至多可下注%s个筹码。\n",
	MSG_HOW_MONEY		: "多少个售筹码？\n",	
	
	MSG_BETTED			: "已有人投注，可跟(genzhu)，加码(jiazhu|raise)或弃牌(qipai|fold)。\n",
	MSG_PLS_BET			: "请下注(xiazhu|bet)。\n",
	MSG_CALL_OR_FOLD	: "你只能选择跟注或弃牌。\n",
	MSG_NOT_LAST		: "还不到最后时刻。\n",
	MSG_NO_FOLD			: "你不可弃牌。\n",
	MSG_NO_HAND_CARD	: "你没有底牌可看。\n",

	MSG_READY			: "$N点头示意已经准备就绪。\n",
				
]);

void refresh_look();

/********************************信息函数***********************************/

//发牌者说话
varargs int dealer_say(string str, mixed* who)
{
	msv(CYN + _dealer[PNAME] + "说道：" + str + NOR, who);
}

/********************************房间函数***********************************/

void create()
{
	_dealer = _localizer->get("dealer") + ({ 0 });

	_localizer->set_safety(_this);

	refresh_look();

	set_notify(_msgs);

	setup();
}

void init()
{
	if(userp(_player)) {
		add_action("do_join", "join");
		add_action("do_look", "look");
		//add_action("do_say", "say");

		add_action("do_buy", "buy");
		add_action("do_sell", "sell");

		add_action("do_ready", ({"ready"}));
		add_action("do_leave", ({"leave"}));

		add_action("do_bet", ({"bet", "xiazhu"}));
		add_action("do_call", ({"call1", "genzhu"}));
		add_action("do_raise", ({"raise", "jiazhu"}));
		add_action("do_fold", ({"fold", "qipai"}));
		add_action("do_show", ({"show"}));
	}
}

//查看场景/底牌
int do_look(string arg)
{
	if(!arg) return _localizer->deskside_look(_this);

	if(arg == "dipai" || arg == "card")	return send_req("hand_card");
	return 0;
}

/********************************准备阶段***********************************/

//加入游戏
int do_join(string arg)
{
	return send_req("join");
}

//加入完成
void on_join(mixed* info)
{
	object who = player_object(info);

	msv("$N在桌边坐下。\n", info);
	if(who) who->move(_this, 1);
}

//入场选手离开
int do_leave(string arg)
{
	return send_req("leave");
}

//离开确认
void on_leave(mixed* info, string arg)
{
	object who = player_object(info);
	int n = to_int(arg);
		
	if(n > 0) {
		_localizer->add_balance(who, n);
		msv("$N退掉了筹码。\n", info);
	}
	msv("$N起身离开了桌子。\n\n", info);
	if(who) who->move(_stand);
}

//入场选手宣布就绪
int do_ready(string arg)
{
	if(_localizer->add_balance(_player, 0) < 0)
		notify_fail("你现在是负资产了，请退掉些筹码。\n");
	return send_req("ready");
}

//就绪确认
void on_ready(mixed* info)
{
	msv("$N点头示意已经准备就绪。\n", info);
}

//买筹码
int do_buy(string arg)
{
	int n;
	if(!arg || sscanf(arg, "%d chip", n) != 1 || n < 1 || n > MAX_EXCHANGE)
		return notify_fail("买筹码：buy <数量> chip。\n");
	return send_req("exchange", n);
}

//卖筹码
int do_sell(string arg)
{
	int n;
	if(!arg || sscanf(arg, "%d chip", n) != 1 || n < 1 || n > MAX_EXCHANGE)
		return notify_fail("退筹码：sell <数量> chip。\n");
	return send_req("exchange", -n);
}

//筹码交易
void on_exchange(mixed* info, string arg)
{
	object who = player_object(info);
	int n = to_int(arg);
	string str = (n > 0) ? "买了" + n : "退了" + (-n);
	
	_localizer->add_balance(_player, -n);
	msv("$N" + str + "筹码。\n", info);
}

/********************************进行阶段***********************************/

//多种方式下注
private void bet(string msg, mixed* who, string arg)
{
	string s1, s2;
	if(sscanf(arg, "%s:%s", s1, s2) != 2) {
		s1 = arg;
		s2 = s1;
	}	
	msv("$N拿出%s个筹码扔在桌子中间。\n", who, s1);
	say(who, sprintf(msg, s2));
}

//下注
int do_bet(string arg)
{
	int n = to_int(arg);
	if(n < 1) return notify_fail("请输入合适的筹码数量。\n");
	
	return send_req("bet", arg);
}

//下注确认
void on_bet(mixed* info, string arg)
{
	bet("%s！\n\n", info, arg);
}

//跟注
int do_call(string arg)
{
	return send_req("call");
}

//跟注确认
void on_call(mixed* info, string arg)
{
	bet("跟了！\n\n", info, arg);
}

//加注
int do_raise(string arg)
{
	int n = to_int(arg);
	if(n < 1) return notify_fail("请输入合适的筹码数量。\n");
	
	return send_req("raise", arg);
}

//加注确认
void on_raise(mixed* info, string arg)
{
	bet("加%d！\n\n", info, arg);
}

//显示底牌
int do_show(string arg)
{
	if(arg == "hand") {
		return send_req("show_hand");
	}
	else if(arg == "down") {

		return 1;
	}
	return 0;
}

//全押确认
void on_show_hand(mixed* info, string arg)
{
	bet("全押！\n\n", info, arg);
}

//弃牌
int do_fold(string arg)
{
	return send_req("fold");
}

void on_fold(mixed* info)
{
	msv("$N合上牌，表示放弃。\n", info);
}

/********************************进行阶段***********************************/

//显示某人的牌
private varargs void show_sb_cards(mixed* who)
{
	msv("\n$N的牌：\n", who);
	msv(draw_cards(who[PCARDS]));
}

//展示发牌过程
void on_dealing(mixed* info)
{	
	dealer_say("开始发牌！\n");
	foreach(mixed* who in _g["players"]) {
		show_sb_cards(who);
	}
}

//提示下一个玩家下注
void on_next_one(mixed* info)
{	
	dealer_say("$N，请下注。\n", info);
}

//游戏结束，奖励胜利者
void on_finish(mixed* who, string arg)
{
	string* arr = explode(arg, ":");

	for(int i = 0; i < sizeof(arr); ++i)
		show_sb_cards(_g[""]who);
		dealer_say(name + "!\n");
	}

	msv("\n");
	dealer_say("$N获胜！\n", who);	
	msv("$N把桌上的筹码搂到自己面前。\n", who);
}

//玩家超时
void on_timeout(mixed* who)
{
	dealer_say("$N超过规定时间，算作弃牌。\n", who);
}


//下一个玩家
int on_next_one(mixed* who)
{
	dealer_say("$N，请下注。\n", who);
}

//查看底牌
void on_look_card(mixed* info, string arg)
{
	object who = player_object(info);
	if(who) {		
		tell_object(who, "你偷偷看了一眼底牌：\n");
		tell_object(who, draw_cards(({ to_int(arg) })));
	}
}

/********************************更新场景***********************************/

/*
string player_str(mixed* u)
{
	int* cards = allocate(_g["round"] + 1);

	for(int i = 0; i < sizeof(cards); ++i) {
		cards[i] = u[PCARDS][i];
	}
	if(!_g["show_hand"]) cards[0] = 29;
	return sprintf("%s:%s:%s:%d:%s",
		u[PNAME],
		u[PID],
		u[PMUD],
		u[PSCORE],
		to_base64(cards)
	);
}

//场景数据序列化成字符串
string scene_str()
{
	string s1 = sprintf("%d;%d",_g["pot"], players_number());
	string s2 = "";
	string s3 = "";
	foreach(mixed* u in _g["players"]) {
		s2 += ";" + player_str(u);
	}
	foreach(mixed* u in _g["queue"]) {
		s3 += ";" + player_str(u);
	}
	return s1 + s2 + s3;
}
*/
//字符串反序列化成玩家数据
mixed* dec_player(string str)
{
	mixed* u = allocate(PCARDS + 1);
	string str;

	sscanf(str, "%s:%s:%s:%d:%s",
		u[PNAME],
		u[PID],
		u[PMUD],
		u[PSCORE],
		str
	);
	u[PCARDS] = from_base64(str);
	return u;
}

//字符串反序列化成场景数据
mapping dec_scene(string scene_str)
{
	string* arr = explode(scene_str, ";");
	int players_size = to_int(arr[1]);
	int queue_size = sizeof(arr) - 2 - players_size;
	mapping g = ([
		"pot"		: to_int(arg[0]), 
		"players"	: allocate(players_size),
		"queue"		: allocate(queue_size);
	]);
	
	for(int i = 0; i < players_size; ++i) {
		g["players"][i] = dec_player(arr[i + 2]);
	}

	for(int i = 0; i < queue_size; ++i) {
		g["queue"][i] = dec_player(arr[i + 2 + players_size]);
	}
	return g;
}

///收到更新场景信息
void on_update_scene(mixed* info, string arg)
{
	_g = dec_scene(arg);
	refresh_look();
}

//刷新房间描述
int refresh_look()
{
	_dealer[PSCORE] = _g["pot"];
	_localizer->refresh_look(_dealer, _g, _this, _stand);
}