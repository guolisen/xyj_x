// by firefox 04/16/2011
// client util

#include <ansi.h>
#include <imud-efun.h>

inherit F_iNODE;

static object_f _localizer;							//���ػ�����
static object_f _stand;								//��̨
static string _server;								//��Ӧ�ķ���������·��
static mapping _msgs;								//֪ͨ��Ϣ��

void client_create()
{
	string* arr = explode(base_name(_this), "/");
	string num = arr[<1][1..];
	_server = arr[<2] + "/s" + num;

	_stand		= __DIR__"stand" + num;
	_localizer	= __DIR__"localizer";
}

//���ֳ��Ϳ�̨������Ϣ
varargs int msv(string str, mixed* who, mixed* target)
{
	return msg_rooms(({_this, _stand}), str, who, target);
}

//ĳ��˵��
varargs int say(mixed* who, string str, mixed* target)
{
	msv(CYN + "$N˵����" + str + NOR, who, target);
}

///����֪ͨ��Ϣ��
void set_notify(mapping msgs)
{
	_msgs = msgs;
}

///�յ�֪ͨ��Ϣ
void on_notify(mixed* info, string arg)
{
	object who = player_object(info);
	int msg_id;
	string str;
	if(sscanf(arg, "%d:%s", msg_id, str) != 2) error("on_notify:wrong arg.\n");
	if(who)	tell_object(who, sprintf(_msgs[msg_id], str));
}

///�յ�������Ϣ
void on_message(mixed* info, string arg)
{
	int msg_id;
	string str;
	if(sscanf(arg, "%d:%s", msg_id, str) != 2) error("on_message:wrong arg.\n");
	msv(sprintf(_msgs[msg_id], str), info);
}

//��ȡ�������
varargs mixed data_of(object who, string prop)
{
	string root = _localizer->get("prop_root");
	mapping m = who->query(root);
	if(!mapp(m)) who->set(root, m = ([]));
	return prop ? m[prop] : m;
}

//���������������
varargs int send_req(string verb, string arg)
{	
	string req = sprintf("%s->%s(%s,%s)",
		_server,
		verb,
		player_gid(player_info()),
		or2(arg, "")
	);

	iMUD_NET_D->send_msg(SERVER_ID, req);
	write("�����ѷ��͡�\n");

	return 1;
}

/*
//���˵��
int do_say(string arg)
{
	if(!arg) arg = "������";
	msv("$N˵����" + arg + "\n");
	return 1;
}
*/