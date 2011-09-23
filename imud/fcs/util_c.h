#ifndef IMUD_UTIL_C_H_INCLUDED
#define IMUD_UTIL_C_H_INCLUDED
// by firefox 04/16/2011
// client util

static mapping _notify_msgs = 0;

///设置通知消息表
void set_notify(mapping msgs)
{
	_notify_msgs = msgs;
}

///客户端获得通知信息
varargs int on_notify(mapping info)
{
	string str = sprintf(_msgs[msg_id], arg1);
	return notify_ok(str);
}


///获取当前mud的id
string mud_id()
{
	return "xyj-cn";
}

///根据对象信息查找对象
object info_ob(mapping info)
{
	if(info["mid"] == mud_id())
		return find_player(info["id"]);
	return 0;
}


//向服务器发送请求
varargs int send_req(string verb, mixed arg, string req_msg)
{
	mapping info;

	if(mapp(arg)) info = arg;
	else if(userp(arg)) info = (["id" : getuid(arg)]);
	else info = ([]);

	if(req_msg) write(req_msg);
	info["mid"] = MUD_ID;
	//src//info["game"] = "fcs0";		//消息路由

	{
		string server = __DIR__"s0";
		server->recv_req(verb, info);
	}


	return 1;
}

//接受来自服务器接的请求
varargs int recv_req(string verb, mapping info)
{
	mixed* ret = evaluate(verb, info);

	return 1;
}


#endif

