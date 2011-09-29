// by firefox 04/16/2011
// client util

#include <imud-efun.h>


//ͨ�ñ���
static object_f _localizer;							//���ػ�����
static object_f _stand;								//��̨
static string _server;								//�ͻ��˶�Ӧ����
static mapping _msgs;								//֪ͨ��Ϣ��

void client_create()
{
	string* arr = explode(base_name(_this), "/");
	string num = arr[<1][1..];
	_server = arr[<2] + "/c" + num;

	_stand		= __DIR__"stand" + num;
	_localizer	= __DIR__"localizer";
}

///����֪ͨ��Ϣ��
void set_notify(mapping msgs)
{
	_msgs = msgs;
}


///���÷���RPC��������fun_str��fun_name(pname:pid:pmud,arg)
void invoke(string fun_str)
{
	string fun, gid, arg;
	mixed* who;

	if(sscanf(fun_str, "%s(%s,%s)", fun, gid, arg) != 3) return;
	who = gid_player(gid);

	call_other(_this, fun, who, arg);
	listen(who);
}

///���֪ͨ��Ϣ
void on_notify(mixed* info, string arg)
{
	object who = player_object(info);
	int msg_id;
	string str;
	if(sscanf(arg, "%d:%s", msg_id, str) != 2) error("on_notify:wrong arg.\n");
	if(who)	tell_object(who, sprintf(_msgs[msg_id], str));
}

//��ù�����Ϣ
void on_message(mixed* info)
{
	msv(_msgs[], info);	
}




///��ȡ��ǰmud��id
string mud_id()
{
	return "xyj-cn";
}

///���ݶ�����Ϣ���Ҷ���
object info_ob(mixed* info)
{
	if(info["mid"] == mud_id())
		return find_player(info["id"]);
	return 0;
}

//��õ�ǰ�����Ϣ
mixed* this_info()
{
	object who = this_player();
	if(who) return ({_player->query("name"), getuid(_player), MUD_ID});
	return 0;
}


//��ȡ�������
varargs mixed data_of(object who, string prop)
{
	string root = _localizer->get("prop_root");
	mapping m = who->query(root);
	if(!mapp(m)) who->set(root, m = ([]));
	return prop ? m[prop] : m;
}

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


//���������������
varargs int send_req(string verb, string arg)
{	
	string req = sprintf("%s->%s(%s,%s)",
		_server,
		verb,
		player_gid(who),
		or2(arg, "")
	);

	iMUD_NET_D->send_msg(SERVER_ID, req);
	write("�����ѷ��͡�\n");

	return 1;
}

//�������Է������ӵ�����
varargs int recv_req(string verb, mixed* info)
{
	mixed* ret = evaluate(verb, info);

	return 1;
}


//���˵��		//todo:
int do_say(string arg)
{
	if(!arg) arg = "������";
	msv("$N˵����" + arg + "\n");
	return 1;
}


//�����ֹ����
int clean_up()
{
	return 0;
}



#endif

