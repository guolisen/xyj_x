// by firefox 04/16/2011
// server util

#include <imud-efun.h>

static mapping _g;								//��Ϸ����
static mapping _listeners;						//��������Ϸ��MUD
static string _client;						//�ͻ��˶�Ӧ����

//������ʾΪ�ַ���(�麯��)
string scene_str();

//��ȡ��Ϸ����
mixed g()
{
	return _g;
}

///��ʼ��������
void server_create()
{
	string* arr = explode(base_name(_this), "/");
	_client = arr[<2] + "/c" + arr[<1][1..];
	_listeners = ([]);
}

///�ͻ��˼�������Ϸ
int listen(mixed* info)
{
	_listeners[info[PMUD]] = time();
}

///����ߵļ���MUD����ˢ����Ϣ
varargs int refresh_all(string fun, mixed* who, string arg)
{
	int	thr = time() - 2 * ALIVE_INERVAL;	
	string req = sprintf("%s->%s(%s,%s)[%s]",
		_client,
		fun,
		player_gid(who),
		or2(arg, ""),
		scene_str()
	);

	foreach(string mud, int time in _listeners) {
		if(time > thr) iMUD_NET_D->send_msg(mud, req);
	}
	return 1;
}

///��ͻ��˷���֪ͨ��Ϣ
varargs int notify(mixed* who, int msg_id, string arg)
{
	string req = sprintf("%s->on_notify(%s,%d:%s)",
		_client,
		player_gid(who),
		msg_id,
		or2(arg, "")
	);

	iMUD_NET_D->send_msg(who[PMUD], req);
	return 0;
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


