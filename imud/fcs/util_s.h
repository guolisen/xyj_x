#ifndef IMUD_UTIL_S_H_INCLUDED
#define IMUD_UTIL_S_H_INCLUDED
// by firefox 04/16/2011
// server util

mapping _g;									//游戏数据
mapping _listeners;							//监听本游戏的MUD
string _client;								//客户端对应对象

//场景表示为字符串(虚函数)
string scene_str();

//获取游戏数据
mixed g()
{
	return _g;
}

///初始化服务器
void server_init(mapping g, string name)
{
	_g = g;
	_listeners = ([]);
	_client = name + "/" + 
	_game_id	= path_file(__FILE__)[0] - '0';
}

///向客户端发送通知信息
int notify(mixed* info, mixed msg)
{
	string msg = sprintf("%s->%s(%s)", _client, "on_notify", implode(info, ":"));
	ICE->send_msg(mud, msg);
	return 0;
}

///客户端监听本游戏
int listen(mixed* info)
{
	_listeners[info[PMUD]] = time();
}

///所有监听MUD发送刷新消息
int refresh_all(mixed* info, string verb)
{
	int	thr = time() - 5*60;
	string msg = implode(info, ":");

	string msg = sprintf("%s->%s(%s)[%s]", _client, verb, implode(info, ":"), scene_str());

	foreach(string mud, int time in _listeners) {
		if(time > thr) ICE->send_msg(mud, msg);
	}
	return 1;
}

///调用分派函数
void invoke(string fun)
{
	string who, list;
	mixed* info;

	if(sscanf(fun, "%s(%s)", fun, who) != 2) return;
	info = explode(who, ":");

	evaluate(fun, info);
	listen(info);
}


#endif

