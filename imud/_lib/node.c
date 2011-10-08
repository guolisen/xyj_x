// firefox 04/16/2011
// C/S共用部分

#include <imud-efun.h>

mapping _listeners = ([]);


///添加远程监听者
void add_listener(mixed* info)
{
	_listeners[info[PMUD]] = time();	
}

///分派调用
void invoke(string fun_str)
{
	string fun, gid, arg;
	mixed* info;
	
	if(sscanf(fun_str, "%s(%s,%s)", fun, gid, arg) != 3) error("invoke invalid arg.\n");
	info = gid_player(gid);	
	
	add_listener(info);
	call_other(_this, fun, info, arg);

}


///向或者的监听MUD发送刷新消息
varargs int reply(string peer_name, string fun, mixed* who, mixed arg)
{
	string req = sprintf("%s->%s(%s,%s)",
		peer_name,
		fun,
		player_gid(who),
		(undefinedp(arg) ? "" : "" + arg),
	);

	ICE_D->send_msg(who[PMUD], req);
	return 1;
}

