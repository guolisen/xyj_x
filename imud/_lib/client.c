// by firefox 04/16/2011
// client util

#include <ansi.h>
#include <imud-efun.h>

inherit F_iNODE;

static object_f _localizer;							//���ػ�����
static object_f _stand;								//��̨
static string _server;								//��Ӧ�ķ���������·��
static mapping _msgs;								//֪ͨ��Ϣ��

///��ʼ���ͻ���
void client_create(mapping msgs)
{
	string dir = file_dir();
	string* arr = explode(base_name(_this), "/");
	string num = arr[<1][1..];
	_server = arr[<2] + "/s" + num;

	_stand		= dir + "/stand" + num;
	_localizer	= dir + "/localizer";
	
	_msgs = msgs;
}

//���ֳ��Ϳ�̨������Ϣ - ����
varargs int msv(string str, mixed* who, mixed arg1, mixed arg2)
{
	str = sprintf(str, arg1, arg2);
	return msg_rooms(({_this, _stand}), str, who);
}

//���ֳ��Ϳ�̨������Ϣ - ����
varargs int msv2(string str, mixed* who, mixed* target, mixed arg1, mixed arg2)
{
	str = sprintf(str, arg1, arg2);
	return msg_rooms(({_this, _stand}), str, who, target);
}

//ĳ��˵��
varargs int say(mixed* who, string str)
{
	msv(CYN + "$N˵����" + str + NOR, who);
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
varargs int send_req(string verb, mixed arg, object who, int silence)
{
	if(!silence && !cd_start(_player, "cmd", 3)) return notify_ok("���������������\n");
	else {
		string req = sprintf("%s->%s(%s,%s)",
			_server,
			verb,
			player_gid(player_info(who)),
			to_s(arg)
		);

		ICE_D->send_msg(SERVER_ID, req);
		ICE_D->flush();
		if(!silence) write("�����ѷ��͡�\n");
	}
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

//�ҵ�����/�ۿ���Ϸ�Ļ���
private object find_iob()
{
	foreach(object ob in all_inventory()) {
		if(interactive(ob)) return ob;
	}
	foreach(object ob in all_inventory(load_object(_stand))) {
		if(interactive(ob)) return ob;
	}
	return 0;
}

static int _check_time = 0;

//����Ƿ�����ҹ�ע����Ϸ���Ա��������������Ϣ
int check_players()
{
	int now = time();
	object ob = find_iob();
	
	if(ob && now > _check_time) {
		send_req("add_listener", 0, ob, 1);
		_check_time = now + ALIVE_INERVAL - 10;
		remove_call_out("check_players");
		call_out("check_players", ALIVE_INERVAL);
	}
}

