// by firefox 04/16/2011
// client util

#include <ansi.h>
#include <imud-efun.h>

inherit F_iNODE;

static object_f _localizer;							//本地化对象
static object_f _stand;								//看台
static string _server;								//对应的服务器对象路径
static mapping _msgs;								//通知消息表

///初始化客户端
void client_create(mapping msgs)
{
	string dir = file_dir();
	string* arr = explode(base_name(_this), "/");
	string num = arr[<1][1..];
	_server = arr[<2] + "/s" + num;

	_stand		= dir + "/stand" + num;
	_localizer	= dir + "/localizer";
	
	_msgs = msgs;
}

//向现场和看台发布信息 - 单人
varargs int msv(string str, mixed* who, mixed arg1, mixed arg2)
{
	str = sprintf(str, arg1, arg2);
	return msg_rooms(({_this, _stand}), str, who);
}

//向现场和看台发布信息 - 单人
varargs int msv2(string str, mixed* who, mixed* target, mixed arg1, mixed arg2)
{
	str = sprintf(str, arg1, arg2);
	return msg_rooms(({_this, _stand}), str, who, target);
}

//某人说话
varargs int say(mixed* who, string str)
{
	msv(CYN + "$N说道：" + str + NOR, who);
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
varargs int send_req(string verb, mixed arg, object who, int silence)
{
	if(!silence && !cd_start(_player, "cmd", 3)) return notify_ok("请勿连续发送命令。\n");
	else {
		string req = sprintf("%s->%s(%s,%s)",
			_server,
			verb,
			player_gid(player_info(who)),
			to_s(arg)
		);

		ICE_D->send_msg(SERVER_ID, req);
		ICE_D->flush();
		if(!silence) write("请求已发送。\n");
	}
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

//找到参与/观看游戏的活人
private object find_iob()
{
	foreach(object ob in all_inventory()) {
		if(interactive(ob)) return ob;
	}
	foreach(object ob in all_inventory(load_object(_stand))) {
		if(interactive(ob)) return ob;
	}
	return 0;
}

static int _check_time = 0;

//检查是否有玩家关注该游戏，以便向服务器订阅消息
int check_players()
{
	int now = time();
	object ob = find_iob();
	
	if(ob && now > _check_time) {
		send_req("add_listener", 0, ob, 1);
		_check_time = now + ALIVE_INERVAL - 10;
		remove_call_out("check_players");
		call_out("check_players", ALIVE_INERVAL);
	}
}

