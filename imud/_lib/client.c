// by firefox 04/16/2011
// client util

#include <ansi.h>
#include <imud-efun.h>

inherit F_iNODE;

static object_f _localizer;							//本地化对象
static object_f _stand;								//看台
static string _server;								//对应的服务器对象路径
static mapping _msgs;								//通知消息表

void client_create()
{
	string* arr = explode(base_name(_this), "/");
	string num = arr[<1][1..];
	_server = arr[<2] + "/s" + num;

	_stand		= __DIR__"stand" + num;
	_localizer	= __DIR__"localizer";
}

//向现场和看台发布信息
varargs int msv(string str, mixed* who, mixed* target)
{
	return msg_rooms(({_this, _stand}), str, who, target);
}

//某人说话
varargs int say(mixed* who, string str, mixed* target)
{
	msv(CYN + "$N说道：" + str + NOR, who, target);
}

///设置通知消息表
void set_notify(mapping msgs)
{
	_msgs = msgs;
}

///收到通知信息
void on_notify(mixed* info, string arg)
{
	object who = player_object(info);
	int msg_id;
	string str;
	if(sscanf(arg, "%d:%s", msg_id, str) != 2) error("on_notify:wrong arg.\n");
	if(who)	tell_object(who, sprintf(_msgs[msg_id], str));
}

///收到公开信息
void on_message(mixed* info, string arg)
{
	int msg_id;
	string str;
	if(sscanf(arg, "%d:%s", msg_id, str) != 2) error("on_message:wrong arg.\n");
	msv(sprintf(_msgs[msg_id], str), info);
}

//获取玩家数据
varargs mixed data_of(object who, string prop)
{
	string root = _localizer->get("prop_root");
	mapping m = who->query(root);
	if(!mapp(m)) who->set(root, m = ([]));
	return prop ? m[prop] : m;
}

//向服务器发送请求
varargs int send_req(string verb, string arg)
{	
	string req = sprintf("%s->%s(%s,%s)",
		_server,
		verb,
		player_gid(player_info()),
		or2(arg, "")
	);

	iMUD_NET_D->send_msg(SERVER_ID, req);
	write("请求已发送。\n");

	return 1;
}

/*
//跨服说话
int do_say(string arg)
{
	if(!arg) arg = "．．．";
	msv("$N说道：" + arg + "\n");
	return 1;
}
*/