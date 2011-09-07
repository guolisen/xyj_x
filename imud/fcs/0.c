// by firefox 04/16/2011

inherit ROOM;

#include "fcs.h"
#include "score.c"

#define CHK_FAIL_STARTED			if(_g["round"] > 0) return notify_ok("游戏已经开始了。\n")
#define CHK_FAIL_NOT_START			if(!_g["round"]) return notify_ok("游戏还未开始。\n")
#define CHK_FAIL_NOT_YOU(who)		if(turn_who() != (who)) return notify_ok("还没轮到你。\n");
#define CHK_OOC(who, cn)			if(who["chip"] < (cn)) return notify_ok("你没有足够的筹码。\n");

#define CHK_CHIP_TOO_LESS(n)		if((n) < 1) return notify_ok("至少要一个筹码。\n");
#define CHK_CHIP_TOO_MUCH(n)		if((n) > _g["max_bet"]) return notify_ok("至多可下注" + _g["max_bet"] + "。\n");


int next_one();
void reward_winner(mapping who);
int start();

/********************************信息函数***********************************/

//向现场和看台发布信息
varargs int msv(string str, mapping who, mapping target)
{
	return msg_rooms(({_this, _stand}), str, who, target);
}

//某人说话
varargs int say(mapping who, string str)
{
	msv(CYN + "$N说道：" + str + NOR, who);
}

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
	fcs_init();
	_localizer->set_safety(_this);
	refresh_look();
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

/********************************动作函数***********************************/

//加入游戏
int do_join(string arg)
{
	CHK_FAIL_STARTED;
	
	if(sizeof(_g["queue"]) < MAX_PLAYER) {
		object ob = this_player();
		mapping m = data_of(ob);
		mapping who = find_info(ob, _g["queue"]);
		if(who) return notify_ok("你已经加入了。\n");
		
		who = ([
			"mid"		: MUD_ID,
			"id"		: getuid(ob),
			"name"		: ob->query("name"),
			"title"		: ob->query("title"),			
			"chip"		: m["chip"],
			"cards"		: allocate(MAX_CARD),
		]);
		m["chip"] = 0;
		_g["queue"] += ({ who });
		msv("$N在桌边坐下。\n", who);
		refresh_look();
		ob->set_temp("block_msg/all", 1);
		ob->move(_this);
		ob->save();
		ob->set_temp("block_msg/all", 0);
		return 1;
	}
	return notify_ok("桌边已经坐满了。\n");
}


//入场选手离开
int do_leave(string arg)
{
	object ob = this_player();
	mapping who = find_info(ob, _g["queue"]);

	CHK_FAIL_STARTED;

	if(who) {
		mapping m = data_of(ob);

		m["chip"] = who["chip"];
		_g["queue"] -= ({ who });
		msv("$N起身离开了桌子。\n\n", who);
		refresh_look();
		ob->move(_stand);
		ob->save();
		return 1;
	}
	return notify_ok("你没加入游戏。\n");
}

//入场选手宣布就绪
int do_ready(string arg)
{
	mapping who = find_info(this_player(), _g["queue"]);
	
	CHK_FAIL_STARTED;
	if(!who) return notify_ok("你没加入游戏。\n");
	if(who["chip"] < MIN_CHIP) return notify_ok("你的筹码太少。\n");

	who["ready"] = 1;
	
	msv("$N点头示意已经准备就绪。\n", who);

	//判读可否开始
	if(sizeof( _g["queue"]) < MIN_PLAYER) return 1;
	foreach(mapping m in _g["queue"]) {
		if(!m["ready"]) return 1;
	}
	
	start();
	return 1;
}

//查看场景/底牌
int do_look(string arg)
{
	if(!arg) return _localizer->deskside_look(_this);

	if(arg == "dipai" || arg == "card") {
		mapping who = this_info();

		if(!who) return notify_ok("你没有底牌可看。\n");
		write("你偷偷看了一眼底牌：\n");
		write(draw_cards(({ who["cards"][0] })));
		return 1;
	}
	return 0;
}

//跨服说话		//todo:
int do_say(string arg)
{
	if(!arg) arg = "．．．";
	msv("$N说道：" + arg + "\n");
	return 1;
}

//买筹码
int do_buy(string arg)
{
	mapping who = find_info(this_player(), _g["queue"]);
		
	if(arg != "chip") return notify_ok("这里只售筹码(chip)。\n");
	CHK_FAIL_STARTED;
	if(!who) return notify_ok("你没参与游戏。\n");
	
	if(_localizer->exchange_chip(this_player(), 1000)) {
		who["chip"] += 1000;
		msv("$N向"DEALER_NAME"买了一千筹码。\n", who);
		refresh_look();
	}
	return 1;
}

//卖筹码
int do_sell(string arg)
{
	mapping who = find_info(this_player(), _g["queue"]);
	
	if(arg != "chip") return notify_ok("这里只可以退售筹码(chip)。\n");
	CHK_FAIL_STARTED;
	if(!who) return notify_ok("你没参与游戏。\n");
	CHK_OOC(who, 1000);
	
	if(_localizer->exchange_chip(this_player(), -1000)) {
		who["chip"] -= 1000;
		msv("$N向"DEALER_NAME"退了一千筹码。\n", who);
		refresh_look();
	}
	return 1;
}


//下注
int sb_bet(mapping who, int n)
{
	who["chip"] -= n;
	who["bet"] += n;
	_g["pot"] += n;
	if(n > _g["bet"]) _g["bet"] = n;
	msv("$N拿出" + n + "个筹码扔在桌子中间。\n", who);
}

//下注
int do_bet(string arg)
{
	mapping who = this_info();
	int n = to_int(arg);
	
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);
	
	if(_g["bet"]) return notify_ok("已经有人投注，可跟(genzhu)或加码(jiazhu)。\n");

	CHK_CHIP_TOO_LESS(n);
	CHK_CHIP_TOO_MUCH(n);
	CHK_OOC(who, n);

	sb_bet(who, n);	
	say(who, n + "!\n");

	return next_one();
}

//跟注
int do_call(string arg)
{
	mapping who = this_info();
	int n;

	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);	
	if(!_g["bet"]) return notify_ok("请下注(xiazhu)。\n");

	n = _g["bet"] - who["bet"];

	CHK_OOC(who, n);

	sb_bet(who, n);
	say(who, "跟了！\n\n");

	return next_one();
}

//加注
int do_raise(string arg)
{
	mapping who = this_info();
	int add = to_int(arg);
	int n = _g["bet"] + add;
	
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);

	if(!_g["bet"]) return notify_ok("请下注(xiazhu)。\n");
	if(who["bet"] > 0) return notify_ok("你只能选择跟注或弃牌。\n");
	CHK_CHIP_TOO_LESS(add);
	CHK_CHIP_TOO_MUCH(n);	
	CHK_OOC(who, n);

	sb_bet(who, n);
	say(who, "加" + add + "！\n\n");

	return next_one();
}

//显示底牌
int do_show(string arg)
{
	if(arg == "hand") {
		mapping who = this_info();
		int n = _g["max_bet"];
		if(_g["round"] < MAX_CARD - 1) return notify_ok("还不到最后时刻。\n");

		CHK_FAIL_NOT_START;
		CHK_FAIL_NOT_YOU(who);
		CHK_OOC(who, n);

		sb_bet(who, n);
		say(who, "全押！\n\n");

		return next_one();
	}
	else if(arg == "down") {

		return 1;
	}
	return 0;
}

//弃牌
int fold(mapping who)
{
	_g["queue"] += ({ who });
	_g["players"] -= ({ who });
}

//弃牌
int do_fold(string arg)
{
	mapping who = this_info();
	
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);

	if(!_g["pot"]) return notify_ok("你不可弃牌。\n");

	fold(who);

	msv("$N合上牌，无奈的摇摇头。\n", who);
	say(who, "放弃...\n\n");
	
	return next_one();
}

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

//展示发牌过程
void dealing()
{
	int min_chip = _g["players"][0]["chip"];

	_g["round"]++;
	
	dealer_say("开始发牌！\n");
	for(int i = 0; i < players_number(); ++i) {
		mapping who = _g["players"][i];
		show_sb_cards(who);
		//call_out("show_sb_cards", PULSE * (i + 1), _g["players"][i]);
		
		if(who["chip"] < min_chip) min_chip = who["chip"];
	}

	//限制下注
	_g["max_bet"] = min_chip / (MAX_CARD  - _g["round"]);

	//计算下注顺序
	turn_init();
	_g["bet"] = 0;

	next_one();
}

//奖励胜利者
void reward_winner(mapping who)
{
	msv("\n");
	dealer_say("$N获胜！\n", who);
	
	who["chip"] += _g["pot"];
	_g["pot"] = 0;

	msv("$N把桌上的筹码搂到自己面前。\n", who);
}

//计算赢家
void finish()
{
	mixed* players = _g["queue"] + _g["players"];

	if(players_number() == 1) {
		reward_winner(_g["players"][0]);
	} else {
		int* max_score = ({-1});
		mapping winner;
		foreach(mapping who in _g["players"]) {
			int* score = cards_score(who["cards"]);
			show_sb_cards(who, 1);
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
	mapping who = turn_who();

	dealer_say("$N超过规定时间，算作弃牌。\n", who);
	fold(who);
	next_one();
}


//下一个玩家
int next_one()
{
	mapping who;

	refresh_look();

	for(int i = 0; i < MAX_PLAYER; ++i) {
		_g["turn"] = (_g["turn"] + 1) % MAX_PLAYER;
		who = turn_who();
		if(who) break;
	}
	remove_call_out("wait_timeout");	
	if(players_number() == 1) {
		finish();
	} else if(!_g["bet"] || who["bet"] < _g["bet"]) {	//还未下注或需要跟别人的加注
		
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

//游戏开始
int start()
{
	foreach(mapping m in _g["queue"]) {
		m["ready"] = 0;
		m["bet"] = 0;
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
			_g["players"][i]["cards"][j] = _g["cards"][i*MAX_CARD + j];
	}
	dealing();
	return 1;
}

//游戏结束
int stop()
{

}



