// by firefox 04/16/2011

inherit ROOM;

#include "fcs.h"
#include "score.c"
#include "msg.h"
#include "util_c.h"


/********************************数据定义***********************************/

mapping _dealer;				//发牌者

static mapping _msgs = ([

	MSG_STARTED			: "游戏已经开始了。\n",
	MSG_NOT_START		: "游戏还未开始。\n",
	MSG_NOT_YOU			: "还没轮到你。\n",
	MSG_JOINED			: "你已经加入了。\n",
	MSG_NOT_JOIN		: "你没加入游戏。\n",
	MSG_FULL			: "桌边已经坐满了。\n",

	MSG_NOT_ENOUGH		: "你没有足够的筹码。\n",
	MSG_AT_LEAST_1		: "至少要一个筹码。\n",
	MSG_TOO_LESS		: "至少要有%d筹码。\n",
	MSG_TOO_MUCH		: "至多可下注%d个筹码。\n",
	MSG_HOW_MONEY		: "多少个售筹码？\n",	
	
	MSG_BETTED			: "已有人投注，可跟(genzhu)，加码(jiazhu|raise)或弃牌(qipai|fold)。\n",
	MSG_PLS_BET			: "请下注(xiazhu|bet)。\n",
	MSG_CALL_OR_FOLD	: "你只能选择跟注或弃牌。\n",
	MSG_NOT_LAST		: "还不到最后时刻。\n",
	MSG_NO_FOLD			: "你不可弃牌。\n",
	MSG_NO_HAND_CARD	: "你没有底牌可看。\n",
		
	MSG_READY			: "$N点头示意已经准备就绪。\n",
				
]);


int next_one();
void reward_winner(mapping who);
int start();

/********************************信息函数***********************************/


//发牌者说话
varargs int dealer_say(string str, mapping who)
{
	if(who) str = replace_string(str, "$N", name_id(who));

	msv(CYN + _dealer["name"] + "说道：" + str + NOR);
}


//刷新房间描述
int refresh_look()
{
	string desc;
	_dealer["chip"] = _g["pot"];
	_localizer->refresh_look(_dealer, _g, _this, _stand);
}

/********************************房间函数***********************************/

void create()
{

	_dealer		= ([]) + _localizer->get("dealer");

	fcs_init();
	_localizer->set_safety(_this);
	refresh_look();

	set_notify(_msgs);

	setup();
}

int clean_up()
{
	return 0;
}

void init()
{
	if(userp(this_player())) {

		add_action("do_join", "join");
		add_action("do_look", "look");
		//add_action("do_say", "say");

		add_action("do_buy", "buy");
		add_action("do_sell", "sell");

		add_action("do_ready",({"ready"}));
		add_action("do_leave",({"leave"}));

		add_action("do_bet",({"bet", "xiazhu"}));
		add_action("do_call",({"call1", "genzhu"}));
		add_action("do_raise",({"raise", "jiazhu"}));
		add_action("do_fold",({"fold", "qipai"}));
		add_action("do_show",({"show"}));
	}
}



//跨服说话		//todo:
int do_say(string arg)
{
	if(!arg) arg = "．．．";
	msv("$N说道：" + arg + "\n");
	return 1;
}


//查看场景/底牌
int do_look(string arg)
{
	if(!arg) return _localizer->deskside_look(_this);

	if(arg == "dipai" || arg == "card") {
		mapping who = this_info();

		if(!who) return notify(MSG_NO_HAND_CARD);
		write("你偷偷看了一眼底牌：\n");
		write(draw_cards(({ who["cards"][0] })));
		return 1;
	}
	return 0;
}

/********************************准备阶段***********************************/

//加入游戏
int do_join(string arg)
{
	object who = this_player();
	mapping info = ([
		"id"		: getuid(who),
		"name"		: filter_color(who->query("name")),
	]);

	return send_req("join", info, "你准备加入游戏。\n");
}

//加入完成
void on_join(mapping info)
{
	object who = info_ob(info);

	msv("$N在桌边坐下。\n", info);
	refresh_look();
	
	if(who) {
		who->set_temp("block_msg/all", 1);
		who->move(_this);
		who->set_temp("block_msg/all", 0);
	}
}

//入场选手离开
int do_leave(string arg)
{
	return send_req("join", this_player(), "你准备离开。\n");
}

//离开确认
void on_leave(mapping info)
{
	object who = info_ob(info);
		
	if(info["chip"] > 0) {
		_localizer->exchange_chip(who, -info["chip"]);		
		msv("$N退掉了筹码。\n", info);
	}
	msv("$N起身离开了桌子。\n\n", info);
	refresh_look();
	if(who) who->move(_stand);
}

//入场选手宣布就绪
int do_ready(string arg)
{
	return send_req("ready", this_player(), "你已就绪。\n");
}

//买筹码
int do_buy(string arg)
{
	int n;
	if(!arg || sscanf(arg, "%d chip", n) != 1 || n < 1)
		return notify_fail("买筹码：buy <数量> chip。\n");
		
	if(!_localizer->exchange_chip(this_player(), n)) return 1;	//先交款，失败退还
	
	return send_req("exchange", this_player(), "你准备买筹码。\n");
}

//卖筹码
int do_sell(string arg)
{
	int n;
	if(!arg || sscanf(arg, "%d chip", n) != 1 || n < 1)
		return notify_fail("退筹码：sell <数量> chip。\n");
	return send_req("exchange", this_player(), "你准备退筹码。\n");
}

//筹码交易
void on_exchange(mapping info)
{
	object who = info_ob(info);
	int n = 0;
	
	if(?) {	//兑换失败，撤销
		on_notify(info);
		_localizer->exchange_chip(who, -n);
	} else {
		string str = (n > 0) ? "买了" + n : "退了" + (-n);
		msv("$N向"DEALER_NAME + str + "筹码。\n", info);
		refresh_look();
	}
}

/********************************进行阶段***********************************/

//下注
int do_bet(string arg)
{
	int n = to_int(arg);
	if(n < 1) return notify_fail("请输入合适的筹码数量。\n");
	
	return send_req("bet", this_player(), "你准备下注。\n");
}

//跟注
int do_call(string arg)
{
	return send_req("call", this_player(), "你准备跟了。\n");
}

//加注
int do_raise(string arg)
{
	int n = to_int(arg);
	if(n < 1) return notify_fail("请输入合适的筹码数量。\n");
	
	return send_req("raise", this_player(), "你准备加码。\n");
}

//显示底牌
int do_show(string arg)
{
	if(arg == "hand") {
		return send_req("call", this_player(), "你准备全压。\n");
	}
	else if(arg == "down") {

		return 1;
	}
	return 0;
}

//下注
void on_bet(mapping info)
{
	string* arr = ({
		CYN"%s说道：%d！\n\n",
		CYN"%s说道：跟了！\n\n",
		CYN"%s说道：加%d！\n\n",
		CYN"%s说道：全押！\n\n",
	})
	int k = 0;
	int n = 0;
	
	msv("$N拿出%d个筹码扔在桌子中间。\n", who, n);
	msv(arr[k], who, n);
}

//弃牌
int do_fold(string arg)
{
	return send_req("call", this_player(), "你准备弃牌。\n");
}

void on_fold(mapping info)
{
	msv("$N合上牌，表示放弃。\n", who);
	//更新显示
}

/********************************进行阶段***********************************/

//显示某人的牌
varargs void show_sb_cards(mapping who, int all)
{
	int* arr = allocate(_g["round"] + 1);	

	for(int i = 0; i <= _g["round"]; ++i)
		arr[i] = who["cards"][i];
	if(!all) arr[0] = -1;

	msv("\n$N的牌：\n", who);
	msv(draw_cards(arr));
}


