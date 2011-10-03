// by firefox 04/16/2011
// server util

#include <imud-efun.h>

inherit F_iNODE;

static mapping _g;							//游戏数据
static string _client;						//对应客户端对象路径

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
}

///向或者的监听MUD发送刷新消息
varargs int notify_all(string fun, mixed* who, mixed arg)
{
	int	thr = time() - 2 * ALIVE_INERVAL;	
	string req = sprintf("%s->%s(%s,%s)",
		_client,
		fun,
		player_gid(who),
		to_s(arg)
	);

	foreach(string mud, int time in _listeners) {
		if(time > thr) ICE_D->send_msg(mud, req);
	}
	return 1;
}

///向客户端发送通知信息
varargs int notify(mixed* who, int msg_id, mixed arg)
{
	string str = sprintf("%d:%s", msg_id, to_s(arg));
	
	reply(_client, "on_notify", who, str);	
	ICE_D->flush();
	return 1;
}
