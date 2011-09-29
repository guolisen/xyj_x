// by firefox 04/16/2011
// client util

#include <imud-efun.h>


//通用本地
static object_f _localizer;							//本地化对象
static object_f _stand;								//看台
static string _server;								//客户端对应对象
static mapping _msgs;								//通知消息表

void client_create()
{
	string* arr = explode(base_name(_this), "/");
	string num = arr[<1][1..];
	_server = arr[<2] + "/c" + num;

	_stand		= __DIR__"stand" + num;
	_localizer	= __DIR__"localizer";
}

///设置通知消息表
void set_notify(mapping msgs)
{
	_msgs = msgs;
}


///调用分派RPC调用请求，fun_str：fun_name(pname:pid:pmud,arg)
void invoke(string fun_str)
{
	string fun, gid, arg;
	mixed* who;

	if(sscanf(fun_str, "%s(%s,%s)", fun, gid, arg) != 3) return;
	who = gid_player(gid);

	call_other(_this, fun, who, arg);
	listen(who);
}

///获得通知信息
void on_notify(mixed* info, string arg)
{
	object who = player_object(info);
	int msg_id;
	string str;
	if(sscanf(arg, "%d:%s", msg_id, str) != 2) error("on_notify:wrong arg.\n");
	if(who)	tell_object(who, sprintf(_msgs[msg_id], str));
}

//获得公开信息
void on_message(mixed* info)
{
	msv(_msgs[], info);	
}




///获取当前mud的id
string mud_id()
{
	return "xyj-cn";
}

///根据对象信息查找对象
object info_ob(mixed* info)
{
	if(info["mid"] == mud_id())
		return find_player(info["id"]);
	return 0;
}

//获得当前玩家信息
mixed* this_info()
{
	object who = this_player();
	if(who) return ({_player->query("name"), getuid(_player), MUD_ID});
	return 0;
}


//获取玩家数据
varargs mixed data_of(object who, string prop)
{
	string root = _localizer->get("prop_root");
	mapping m = who->query(root);
	if(!mapp(m)) who->set(root, m = ([]));
	return prop ? m[prop] : m;
}

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


//向服务器发送请求
varargs int send_req(string verb, string arg)
{	
	string req = sprintf("%s->%s(%s,%s)",
		_server,
		verb,
		player_gid(who),
		or2(arg, "")
	);

	iMUD_NET_D->send_msg(SERVER_ID, req);
	write("请求已发送。\n");

	return 1;
}

//接受来自服务器接的请求
varargs int recv_req(string verb, mixed* info)
{
	mixed* ret = evaluate(verb, info);

	return 1;
}


//跨服说话		//todo:
int do_say(string arg)
{
	if(!arg) arg = "．．．";
	msv("$N说道：" + arg + "\n");
	return 1;
}


//房间禁止清理
int clean_up()
{
	return 0;
}



#endif

