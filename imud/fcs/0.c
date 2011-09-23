// by firefox 04/16/2011

inherit ROOM;

#include "fcs.h"
#include "score.c"
#include "msg.h"
#include "util_c.h"


static mapping _msgs = ([

	MSG_STARTED			: "��Ϸ�Ѿ���ʼ�ˡ�\n",
	MSG_NOT_START		: "��Ϸ��δ��ʼ��\n",
	MSG_NOT_YOU			: "��û�ֵ��㡣\n",
	MSG_JOINED			: "���Ѿ������ˡ�\n",
	MSG_NOT_JOIN		: "��û������Ϸ��\n",
	MSG_FULL			: "�����Ѿ������ˡ�\n",

	MSG_NOT_ENOUGH		: "��û���㹻�ĳ��롣\n",
	MSG_AT_LEAST_1		: "����Ҫһ�����롣\n",
	MSG_TOO_LESS		: "����Ҫ��%d���롣\n",
	MSG_TOO_MUCH		: "�������ע%d�����롣\n",
	MSG_HOW_MONEY		: "���ٸ��۳��룿\n",	
	
	MSG_BETTED			: "������Ͷע���ɸ�(genzhu)������(jiazhu|raise)������(qipai|fold)��\n",
	MSG_PLS_BET			: "����ע(xiazhu|bet)��\n",
	MSG_CALL_OR_FOLD	: "��ֻ��ѡ���ע�����ơ�\n",
	MSG_NOT_LAST		: "���������ʱ�̡�\n",
	MSG_NO_FOLD			: "�㲻�����ơ�\n",
	MSG_NO_HAND_CARD	: "��û�е��ƿɿ���\n",
				
]);





#define CHK_FAIL_STARTED			if(_g["round"] > 0) return notify(MSG_STARTED)
#define CHK_FAIL_NOT_START			if(!_g["round"]) return notify(MSG_NOT_START)
#define CHK_FAIL_NOT_YOU(who)		if(turn_who() != (who)) return notify(MSG_NOT_YOU);
#define CHK_OOC(who, cn)			if(who["chip"] < (cn)) return notify(MSG_NOT_ENOUGH);

#define CHK_CHIP_TOO_LESS(n)		if((n) < 1) return notify(MSG_AT_LEAST_1);
#define CHK_CHIP_TOO_MUCH(n)		if((n) > _g["max_bet"]) return notify(MSG_TOO_MUCH, _g["max_bet"]);


int next_one();
void reward_winner(mapping who);
int start();

/********************************��Ϣ����***********************************/

//���ֳ��Ϳ�̨������Ϣ
varargs int msv(string str, mapping who, mapping target)
{
	return msg_rooms(({_this, _stand}), str, who, target);
}

//ĳ��˵��
varargs int say(mapping who, string str)
{
	msv(CYN + "$N˵����" + str + NOR, who);
}

//������˵��
varargs int dealer_say(string str, mapping who)
{
	if(who) str = replace_string(str, "$N", name_id(who));

	msv(CYN + _dealer["name"] + "˵����" + str + NOR);
}


//ˢ�·�������
int refresh_look()
{
	string desc;
	_dealer["chip"] = _g["pot"];
	_localizer->refresh_look(_dealer, _g, _this, _stand);
}

/********************************���亯��***********************************/

void create()
{
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

/********************************��������***********************************/

//������Ϸ
int do_join(string arg)
{
	object who = this_player();
	mapping info = ([
		"id"		: getuid(who),
		"name"		: filter_color(who->query("name")),
	]);

	return send_req("join", info);
}

//�������
void on_join(mapping info)
{
	object who = info_ob(info);

	msv("$N���������¡�\n", info);
	refresh_look();
	
	if(who) {
		who->set_temp("block_msg/all", 1);
		who->move(_this);
		who->set_temp("block_msg/all", 0);
	}
}

//�볡ѡ���뿪
int do_leave(string arg)
{
	return send_req("join", this_player());
}

//�볡ѡ���뿪
int do_leave(string arg)
{
	object ob = this_player();
	mapping who = find_info(ob, _g["queue"]);

	CHK_FAIL_STARTED;

	if(!who) notify(MSG_NOT_JOIN);

	//wait for

	if(who["chip"] > 0) {
		_localizer->exchange_chip(this_player(), -who["chip"]);
		msv("$N�˵��˳��롣\n", who);
	}
	_g["queue"] -= ({ who });
	msv("$N�����뿪�����ӡ�\n\n", who);
	refresh_look();
	ob->move(_stand);
	ob->save();
	return 1;
}

//�볡ѡ����������
int do_ready(string arg)
{
	mapping who = find_info(this_player(), _g["queue"]);
	
	CHK_FAIL_STARTED;
	if(!who) return notify(MSG_NOT_JOIN);
	if(who["chip"] < MIN_CHIP) return notify(MSG_TOO_LESS, MIN_CHIP);

	//wait for

	who["ready"] = 1;
	
	msv("$N��ͷʾ���Ѿ�׼��������\n", who);

	//�ж��ɷ�ʼ
	if(sizeof( _g["queue"]) < MIN_PLAYER) return 1;
	foreach(mapping m in _g["queue"]) {
		if(!m["ready"]) return 1;
	}
	
	start();
	return 1;
}

//�鿴����/����
int do_look(string arg)
{
	if(!arg) return _localizer->deskside_look(_this);

	if(arg == "dipai" || arg == "card") {
		mapping who = this_info();

		if(!who) return notify(MSG_NO_HAND_CARD);
		write("��͵͵����һ�۵��ƣ�\n");
		write(draw_cards(({ who["cards"][0] })));
		return 1;
	}
	return 0;
}

//���˵��		//todo:
int do_say(string arg)
{
	if(!arg) arg = "������";
	msv("$N˵����" + arg + "\n");
	return 1;
}

//�����
int do_buy(string arg)
{
	int n;
	string id;
	if(!arg || sscanf(arg, "%d %s", n, id) != 2 || id != "chip" || n < 1)
		return notify_fail("������룺buy <����> chip��\n");

	{
		mapping who = find_info(this_player(), _g["queue"]);

		CHK_FAIL_STARTED;
		if(!who) return notify(MSG_NOT_JOIN);

		//wait for

		if(_localizer->exchange_chip(this_player(), n)) {
			who["chip"] += n;
			msv("$N��"DEALER_NAME"����һǧ���롣\n", who);
			refresh_look();
		}
	}
	return 1;
}

//������
int do_sell(string arg)
{
	mapping who = find_info(this_player(), _g["queue"]);
	int n = to_int(arg);
	
	if(n < 1) return notify(MSG_HOW_MONEY);
	CHK_FAIL_STARTED;
	if(!who) return notify(MSG_NOT_JOIN);
	CHK_OOC(who, n);

	//wait for
	
	if(_localizer->exchange_chip(this_player(), -n)) {
		who["chip"] -= n;
		msv("$N��"DEALER_NAME"����һǧ���롣\n", who);
		refresh_look();
	}
	return 1;
}


//��ע
int sb_bet(mapping who, int n)
{
	who["chip"] -= n;
	who["bet"] += n;
	_g["pot"] += n;
	if(n > _g["bet"]) _g["bet"] = n;
	msv("$N�ó�" + n + "���������������м䡣\n", who);
}

//��ע
int do_bet(string arg)
{
	mapping who = this_info();
	int n = to_int(arg);
	
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);
	
	if(_g["bet"]) return notify(MSG_BETTED);

	CHK_CHIP_TOO_LESS(n);
	CHK_CHIP_TOO_MUCH(n);
	CHK_OOC(who, n);

	//wait for

	sb_bet(who, n);	
	say(who, n + "!\n");

	return next_one();
}

//��ע
int do_call(string arg)
{
	mapping who = this_info();
	int n;

	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);	
	if(!_g["bet"]) return notify(MSG_PLS_BET);

	n = _g["bet"] - who["bet"];

	CHK_OOC(who, n);

	//wait for

	sb_bet(who, n);
	say(who, "���ˣ�\n\n");

	return next_one();
}

//��ע
int do_raise(string arg)
{
	mapping who = this_info();
	int add = to_int(arg);
	int n = _g["bet"] + add;
	
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);

	if(!_g["bet"]) return notify(MSG_PLS_BET);
	if(who["bet"] > 0) return notify(MSG_CALL_OR_FOLD);
	CHK_CHIP_TOO_LESS(add);
	CHK_CHIP_TOO_MUCH(n);	
	CHK_OOC(who, n);

	//wait for

	sb_bet(who, n);
	say(who, "��" + add + "��\n\n");

	return next_one();
}

//��ʾ����
int do_show(string arg)
{
	if(arg == "hand") {
		mapping who = this_info();
		int n = _g["max_bet"];
		if(_g["round"] < MAX_CARD - 1) return notify(MSG_NOT_LAST);

		CHK_FAIL_NOT_START;
		CHK_FAIL_NOT_YOU(who);
		CHK_OOC(who, n);

		//wait for

		sb_bet(who, n);
		say(who, "ȫѺ��\n\n");

		return next_one();
	}
	else if(arg == "down") {

		return 1;
	}
	return 0;
}

//����
int fold(mapping who)
{
	_g["queue"] += ({ who });
	_g["players"] -= ({ who });
}

//����
int do_fold(string arg)
{
	mapping who = this_info();
	
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);

	if(!_g["pot"]) return notify(MSG_NO_FOLD);

	//wait for

	fold(who);

	msv("$N�����ƣ����ε�ҡҡͷ��\n", who);
	say(who, "����...\n\n");
	
	return next_one();
}

//��ʾĳ�˵���
varargs void show_sb_cards(mapping who, int all)
{
	int* arr = allocate(_g["round"] + 1);	

	for(int i = 0; i <= _g["round"]; ++i)
		arr[i] = who["cards"][i];
	if(!all) arr[0] = -1;

	msv("\n$N���ƣ�\n", who);
	msv(draw_cards(arr));
}

//չʾ���ƹ���
void dealing()
{
	int min_chip = _g["players"][0]["chip"];

	_g["round"]++;
	
	dealer_say("��ʼ���ƣ�\n");
	for(int i = 0; i < players_number(); ++i) {
		mapping who = _g["players"][i];
		show_sb_cards(who);
		//call_out("show_sb_cards", PULSE * (i + 1), _g["players"][i]);
		
		if(who["chip"] < min_chip) min_chip = who["chip"];
	}

	//������ע
	_g["max_bet"] = min_chip / (MAX_CARD  - _g["round"]);

	//������ע˳��
	turn_init();
	_g["bet"] = 0;

	next_one();
}

//����ʤ����
void reward_winner(mapping who)
{
	msv("\n");
	dealer_say("$N��ʤ��\n", who);
	
	who["chip"] += _g["pot"];
	_g["pot"] = 0;

	msv("$N�����ϵĳ���§���Լ���ǰ��\n", who);
}

//����Ӯ��
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

//��ҳ�ʱ
void wait_timeout()
{
	mapping who = turn_who();

	dealer_say("$N�����涨ʱ�䣬�������ơ�\n", who);
	fold(who);
	next_one();
}


//��һ�����
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
	} else if(!_g["bet"] || who["bet"] < _g["bet"]) {	//��δ��ע����Ҫ�����˵ļ�ע
		
		dealer_say("$N������ע��\n", who);
		call_out("wait_timeout", PLAYER_TIME);		//todo:
	} 
	else if(_g["round"] < MAX_CARD - 1) {
		dealing();
	} else {
		finish();
	}
	return 1;
}

//��Ϸ��ʼ
int start()
{
	foreach(mapping m in _g["queue"]) {
		m["ready"] = 0;
		m["bet"] = 0;
	}
	_g["players"] = _g["queue"];
	_g["queue"] = ({});

	//ϴ��
	for(int i = 0; i < sizeof(_g["cards"]); ++i) {
		_g["cards"][i] = i;
	}
	shuffle(_g["cards"]);

	//�������
	for(int i = 0; i < players_number(); ++i) {
		for(int j = 0; j < MAX_CARD; ++j)
			_g["players"][i]["cards"][j] = _g["cards"][i*MAX_CARD + j];
	}
	dealing();
	return 1;
}

//��Ϸ����
int stop()
{

}



