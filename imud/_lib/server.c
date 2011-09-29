// by firefox 04/16/2011
// server util

#include <imud-efun.h>

static mapping _g;								//游戏数据
static mapping _listeners;						//监听本游戏的MUD
static string _client;						//客户端对应对象

//场景表示为字符串(虚函数)
string scene_str();

//获取游戏数据
mixed g()
{
	return _g;
}

///初始化服务器
void server_create()
{
	string* arr = explode(base_name(_this), "/");
	_client = arr[<2] + "/c" + arr[<1][1..];
	_listeners = ([]);
}

///客户端监听本游戏
int listen(mixed* info)
{
	_listeners[info[PMUD]] = time();
}

///向或者的监听MUD发送刷新消息
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

///向客户端发送通知信息
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


