// ICE(iMUD Communication Environment)  firefox 04/16/2011

#include <imud-efun.h>

#include <net/dns.h>
#include <net/macros.h>
#include <net/daemons.h>

inherit F_iEFUN;
inherit F_CLEAN_UP;
inherit F_DBASE;

mapping _mudlist = ([
	"xyj-cn"		: ([
		"name"			: "西游记联合站",
		"ip"			: ({"221.238.143.29", "60.28.50.88"}),
		"udpport"		: 2012,
	]),
	"xyj-tj"		: ([
		"name"			: "西游记天津站",
		"ip"			: ({"221.238.143.30", "60.28.50.54"}),
		"udpport"		: 6670,
	])
]);

mapping _msg_queue = ([]);		//发送队列

void incoming_request(mapping info);

///查询本MUD ID
string mud_id()
{
	return DNS_MASTER->query_mud_name();
}

///查询本服务器ID
string server_id()
{
	return "XYJ-CN";			//todo
}
	
///发送消息，格式：fcs/c0->on_bet(火狐:firefox:xyj-cn,n)
int send_msg(string mud, string msg)
{
	if(_msg_queue[mud]) _msg_queue[mud] += ({ msg });
	else _msg_queue[mud] = ({ msg });
	trace("send_msg " + mud + " " + msg);
}

///发送消息(立即)
int send_now(string mud, string msg)
{
	if(mud != mud_id()) {
		mapping minfo = DNS_MASTER->query_mud_info(mud);

		if(!minfo) return 0;		//服务器未联通
		
		msg = replace_string(msg, "|", "");
		msg = replace_string(msg, "@@@", "");

		DNS_MASTER->send_udp(minfo["HOSTADDRESS"], minfo["PORTUDP"],
			"@@@" + "ice" +
			"||NAME:" + Mud_name() +
			"||PORTUDP:" + udp_port() +
			"||MSG:" + msg + "@@@\n"
		);
	} else {	//本地消息不经过网络
		mapping info = (["NAME" : mud, "MSG" : msg]);
		call_out("incoming_request", 0, info);
		//incoming_request(info);
	}
	return 1;
}

///刷新缓冲区，消息集中发送是为避免udp的乱序
int flush()
{
	foreach(string mud, string* arr in _msg_queue) {		
		string str = implode(arr, "#");
		send_now(mud, str);
		_msg_queue[mud] = ({});
	}
	trace("ice flush OK!\n");
	return 1;
}


///收到信息
void incoming_request(mapping info)
{
	mapping minfo = DNS_MASTER->query_mud_info(info["NAME"]);
	string* arr = explode(info["MSG"], "#");
	
	foreach(string msg in arr) {
		string file, fun;
		trace("incoming " + msg);
		if(sscanf(msg, "%s->%s", file, fun) != 2) error("incoming_request: invalid msg.\n");

		if(file_size(iMUD_DIR + file + ".c") > 0)
			(iMUD_DIR + file)->invoke(fun);
	}
}


