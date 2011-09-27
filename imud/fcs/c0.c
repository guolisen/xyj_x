// by firefox 04/16/2011

inherit ROOM;

#include "fcs.h"
#include "cards.c"
#include "msg.h"
#include "util_c.h"


#define ROE						(200*10000/1000)	//���ʣ������뻻1K����
#define DEALER_NAME				"����Ů��"			//

/********************************���ݶ���***********************************/

mapping _g = ([
	"queue"			: ({}),			//�Ŷ������Ϣ
	"players"		: ({}),			//�����Ϣ(mid, name, id, chip)
	"pot"			: 0,				//�ص׳�����	
]);

mapping _dealer;						//������

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
		
	MSG_READY			: "$N��ͷʾ���Ѿ�׼��������\n",
				
]);

void update_scene(string scene)
{
	mixed* args = explode(scene, ",");

}

//���÷���
void invoke(string fun)
{
	string arg, scene;
	if(sscanf(fun, "%s(%s)[%s]", fun, arg, scene) == 3) {	//������������
		update_scene(scene);
	}
	else if(sscanf(fun, "%s(%s)", fun, arg) != 2) return;

	evaluate(fun, explode(arg, ":"));
}

/********************************��Ϣ����***********************************/

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
	_dealer		= ([]) + _localizer->get("dealer");

	fcs_init();
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

		add_action("do_ready",({"ready"}));
		add_action("do_leave",({"leave"}));

		add_action("do_bet",({"bet", "xiazhu"}));
		add_action("do_call",({"call1", "genzhu"}));
		add_action("do_raise",({"raise", "jiazhu"}));
		add_action("do_fold",({"fold", "qipai"}));
		add_action("do_show",({"show"}));
	}
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

/********************************׼���׶�***********************************/

//������Ϸ
int do_join(string arg)
{
	return send_req("join", filter_color(who->query("name"));
}

//�������
void on_join(mixed* args)
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
	return send_req("leave");
}

//�뿪ȷ��
void on_leave(mapping info)
{
	object who = info_ob(info);
		
	if(info["chip"] > 0) {
		_localizer->exchange_chip(who, -info["chip"]);		
		msv("$N�˵��˳��롣\n", info);
	}
	msv("$N�����뿪�����ӡ�\n\n", info);
	refresh_look();
	if(who) who->move(_stand);
}

//�볡ѡ����������
int do_ready(string arg)
{
	return send_req("ready");
}

//�����
int do_buy(string arg)
{
	int n;
	if(!arg || sscanf(arg, "%d chip", n) != 1 || n < 1)
		return notify_fail("����룺buy <����> chip��\n");
		
	if(!_localizer->exchange_chip(_player, n)) return 1;	//�Ƚ��ʧ���˻�
	
	return send_req("exchange", n);
}

//������
int do_sell(string arg)
{
	int n;
	if(!arg || sscanf(arg, "%d chip", n) != 1 || n < 1)
		return notify_fail("�˳��룺sell <����> chip��\n");
	return send_req("exchange", -n);
}

//���뽻��
void on_exchange(mapping info)
{
	object who = info_ob(info);
	int n = 0;
	
	if(?) {	//�һ�ʧ�ܣ�����
		on_notify(info);
		_localizer->exchange_chip(who, -n);
	} else {
		string str = (n > 0) ? "����" + n : "����" + (-n);
		msv("$N��"DEALER_NAME + str + "���롣\n", info);
		refresh_look();
	}
}

/********************************���н׶�***********************************/

/*
rpc���ֳ�һ�������ԣ�call remote->fun(a)
1.��������
2.������������з��ؽ��������͸�on_fun

������1��1
��һ����1�Զ࣬һ�����󷢳�ȥ������server���ݣ�Ȼ��㲥�����пͻ���
*/


//��ע
int do_bet(string arg)
{
	int n = to_int(arg);
	if(n < 1) return notify_fail("��������ʵĳ���������\n");
	
	return send_req("bet", n);
}

//��ע
int do_call(string arg)
{
	return send_req("call");
}

//��ע
int do_raise(string arg)
{
	int n = to_int(arg);
	if(n < 1) return notify_fail("��������ʵĳ���������\n");
	
	return send_req("raise");
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

//��ע��ɣ���ʾ��ע��Ϣ��ˢ����ұ�
void on_bet(mapping info)
{
	//�ص�
	//"players"		: ({}),			//�����Ϣ(mid, name, id, chip)
	object who = info_ob(info);
	string* arr = ({
		CYN"%s˵����%d��\n\n",
		CYN"%s˵�������ˣ�\n\n",
		CYN"%s˵������%d��\n\n",
		CYN"%s˵����ȫѺ��\n\n",
	})
	int k = 0;
	int n = 0;
	
	msv("$N�ó�%d���������������м䡣\n", who, n);
	msv(arr[k], who, n);
}

//����
int do_fold(string arg)
{
	return send_req("fold");
}

void on_fold(mapping info)
{
	msv("$N�����ƣ���ʾ������\n", who);
	//������ʾ
}

/********************************���н׶�***********************************/

//��ʾĳ�˵���
private varargs void show_sb_cards(mapping who, int all)
{
	int* arr = allocate(_g["round"] + 1);	

	for(int i = 0; i <= _g["round"]; ++i)
		arr[i] = who["cards"][i];
	if(!all) arr[0] = -1;

	msv("\n$N���ƣ�\n", who);
	msv(draw_cards(arr));
}


//չʾ���ƹ���
void on_dealing(mixed* info)
{	
	dealer_say("��ʼ���ƣ�\n");													//todo
	for(int i = 0; i < players_number(); ++i) {
		show_sb_cards(who);
	}
}

//����ʤ����
void on_reward_winner(mixed* who)
{
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
	//call_out("wait_timeout", PLAYER_TIME);		//todo:
}

//�鿴����
int on_look_card(mixed* who)
{

}