// by firefox 04/16/2011
// fcs client

#include <imud-efun.h>
#include "fcs.h"

inherit ROOM;
inherit F_iCLIENT;

#include "cards.c"

#define MAX_EXCHANGE			100000				//�һ�����

mixed* _dealer;										//������
mapping _g = (["pot" : 0, "queue" : ({}), "players" : ({})]);

static mapping _msgs = ([

	MSG_STARTED			: "��Ϸ�Ѿ���ʼ�ˡ�\n",
	MSG_NOT_START		: "��Ϸ��δ��ʼ��\n",
	MSG_NOT_YOU			: "��û�ֵ��㡣\n",
	MSG_JOINED			: "���Ѿ������ˡ�\n",
	MSG_NOT_JOIN		: "��û������Ϸ��\n",
	MSG_FULL			: "�����Ѿ������ˡ�\n",

	MSG_NOT_ENOUGH		: "��û���㹻�ĳ��롣\n",
	MSG_AT_LEAST_1		: "����Ҫһ�����롣\n",
	MSG_TOO_LESS		: "����Ҫ��%s�����롣\n",
	MSG_TOO_MUCH		: "�������ע%s�����롣\n",
	MSG_HOW_MONEY		: "���ٸ��۳��룿\n",	
	
	MSG_BETTED			: "������Ͷע���ɸ�(genzhu)������(jiazhu|raise)������(qipai|fold)��\n",
	MSG_PLS_BET			: "����ע(xiazhu|bet)��\n",
	MSG_CALL_OR_FOLD	: "��ֻ��ѡ���ע�����ơ�\n",
	MSG_NOT_LAST		: "���������ʱ�̡�\n",
	MSG_NO_FOLD			: "�㲻�����ơ�\n",
	MSG_NO_HAND_CARD	: "��û�е��ƿɿ���\n",

	MSG_READY			: "$N��ͷʾ���Ѿ�׼��������\n",
				
]);

void refresh_look();

/********************************��Ϣ����***********************************/

//������˵��
varargs int dealer_say(string str, mixed* who)
{
	msv(CYN + _dealer[PNAME] + "˵����" + str + NOR, who);
}

/********************************���亯��***********************************/

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

//�鿴����/����
int do_look(string arg)
{
	if(!arg) return _localizer->deskside_look(_this);

	if(arg == "dipai" || arg == "card")	return send_req("hand_card");
	return 0;
}

/********************************׼���׶�***********************************/

//������Ϸ
int do_join(string arg)
{
	return send_req("join");
}

//�������
void on_join(mixed* info)
{
	object who = player_object(info);

	msv("$N���������¡�\n", info);
	if(who) who->move(_this, 1);
}

//�볡ѡ���뿪
int do_leave(string arg)
{
	return send_req("leave");
}

//�뿪ȷ��
void on_leave(mixed* info, string arg)
{
	object who = player_object(info);
	int n = to_int(arg);
		
	if(n > 0) {
		_localizer->add_balance(who, n);
		msv("$N�˵��˳��롣\n", info);
	}
	msv("$N�����뿪�����ӡ�\n\n", info);
	if(who) who->move(_stand);
}

//�볡ѡ����������
int do_ready(string arg)
{
	if(_localizer->add_balance(_player, 0) < 0)
		notify_fail("�������Ǹ��ʲ��ˣ����˵�Щ���롣\n");
	return send_req("ready");
}

//����ȷ��
void on_ready(mixed* info)
{
	msv("$N��ͷʾ���Ѿ�׼��������\n", info);
}

//�����
int do_buy(string arg)
{
	int n;
	if(!arg || sscanf(arg, "%d chip", n) != 1 || n < 1 || n > MAX_EXCHANGE)
		return notify_fail("����룺buy <����> chip��\n");
	return send_req("exchange", n);
}

//������
int do_sell(string arg)
{
	int n;
	if(!arg || sscanf(arg, "%d chip", n) != 1 || n < 1 || n > MAX_EXCHANGE)
		return notify_fail("�˳��룺sell <����> chip��\n");
	return send_req("exchange", -n);
}

//���뽻��
void on_exchange(mixed* info, string arg)
{
	object who = player_object(info);
	int n = to_int(arg);
	string str = (n > 0) ? "����" + n : "����" + (-n);
	
	_localizer->add_balance(_player, -n);
	msv("$N" + str + "���롣\n", info);
}

/********************************���н׶�***********************************/

//���ַ�ʽ��ע
private void bet(string msg, mixed* who, string arg)
{
	string s1, s2;
	if(sscanf(arg, "%s:%s", s1, s2) != 2) {
		s1 = arg;
		s2 = s1;
	}	
	msv("$N�ó�%s���������������м䡣\n", who, s1);
	say(who, sprintf(msg, s2));
}

//��ע
int do_bet(string arg)
{
	int n = to_int(arg);
	if(n < 1) return notify_fail("��������ʵĳ���������\n");
	
	return send_req("bet", arg);
}

//��עȷ��
void on_bet(mixed* info, string arg)
{
	bet("%s��\n\n", info, arg);
}

//��ע
int do_call(string arg)
{
	return send_req("call");
}

//��עȷ��
void on_call(mixed* info, string arg)
{
	bet("���ˣ�\n\n", info, arg);
}

//��ע
int do_raise(string arg)
{
	int n = to_int(arg);
	if(n < 1) return notify_fail("��������ʵĳ���������\n");
	
	return send_req("raise", arg);
}

//��עȷ��
void on_raise(mixed* info, string arg)
{
	bet("��%d��\n\n", info, arg);
}

//��ʾ����
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

//ȫѺȷ��
void on_show_hand(mixed* info, string arg)
{
	bet("ȫѺ��\n\n", info, arg);
}

//����
int do_fold(string arg)
{
	return send_req("fold");
}

void on_fold(mixed* info)
{
	msv("$N�����ƣ���ʾ������\n", info);
}

/********************************���н׶�***********************************/

//��ʾĳ�˵���
private varargs void show_sb_cards(mixed* who)
{
	msv("\n$N���ƣ�\n", who);
	msv(draw_cards(who[PCARDS]));
}

//չʾ���ƹ���
void on_dealing(mixed* info)
{	
	dealer_say("��ʼ���ƣ�\n");
	foreach(mixed* who in _g["players"]) {
		show_sb_cards(who);
	}
}

//��ʾ��һ�������ע
void on_next_one(mixed* info)
{	
	dealer_say("$N������ע��\n", info);
}

//��Ϸ����������ʤ����
void on_finish(mixed* who, string arg)
{
	string* arr = explode(arg, ":");

	for(int i = 0; i < sizeof(arr); ++i)
		show_sb_cards(_g[""]who);
		dealer_say(name + "!\n");
	}

	msv("\n");
	dealer_say("$N��ʤ��\n", who);	
	msv("$N�����ϵĳ���§���Լ���ǰ��\n", who);
}

//��ҳ�ʱ
void on_timeout(mixed* who)
{
	dealer_say("$N�����涨ʱ�䣬�������ơ�\n", who);
}


//��һ�����
int on_next_one(mixed* who)
{
	dealer_say("$N������ע��\n", who);
}

//�鿴����
void on_look_card(mixed* info, string arg)
{
	object who = player_object(info);
	if(who) {		
		tell_object(who, "��͵͵����һ�۵��ƣ�\n");
		tell_object(who, draw_cards(({ to_int(arg) })));
	}
}

/********************************���³���***********************************/

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

//�����������л����ַ���
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
//�ַ��������л����������
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

//�ַ��������л��ɳ�������
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

///�յ����³�����Ϣ
void on_update_scene(mixed* info, string arg)
{
	_g = dec_scene(arg);
	refresh_look();
}

//ˢ�·�������
int refresh_look()
{
	_dealer[PSCORE] = _g["pot"];
	_localizer->refresh_look(_dealer, _g, _this, _stand);
}