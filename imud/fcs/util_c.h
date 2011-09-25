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

///获得通知信息
void on_notify(mapping info)
{
	string str = sprintf(_msgs[msg_id], arg1);
	notify_ok(str);
}

//获得公开信息
void on_message(mapping info)
{
	msv(_msgs[], info);	
}

//通用本地
object_f _localizer;			//本地化对象
object_f _stand;				//看台

void init_c()
{
	_game_id	= path_file(__FILE__)[0] - '0';
	_stand		= __DIR__"stand" + _game_id;

	_localizer	= __DIR__"localizer";
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

//获得玩家信息
mapping this_info()
{	
	return find_info(_player, _g["players"]);
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
	mapping info = ([
		"mid"		: 0,
		"id"		: getuid(_player),
		"verb"		: verb,
		"arg"		: arg,
	]);

	//"from:%s@%s,call
	write("请求已发送。\n");
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

