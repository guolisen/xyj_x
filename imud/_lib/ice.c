// ICE(iMUD Communication Environment)  firefox 04/16/2011

#include <imud.h>

#include <net/dns.h>
#include <net/macros.h>
#include <net/daemons.h>

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

///查询本MUD ID
string mud_id()
{
	return DNS_MASTER->query_mud_name();
}

///查询本服务器ID
string server_id()
{
	return "";			//todo
}
/*
 + 

	fcs/s0->join(火狐:firefox:xyj-cn:0) 
	fcs/s0->bet(火狐:firefox:xyj-cn:n) 
	fcs/c0->on_bet(火狐:firefox:xyj-cn:n)[pot,players,火狐:firefox:xyj-cn:20] '
	*/


//发送消息
int send_msg(string mud, string msg)
{
	mapping minfo = DNS_MASTER->query_mud_info(mud);

	if(!minfo) return 0;		//服务器未联通
	
	msg = replace_string(msg, "|", "");
	msg = replace_string(msg, "@@@", "");

	DNS_MASTER->send_udp(minfo["HOSTADDRESS"], minfo["PORTUDP"],
		"@@@" + "ICE" +
		"||NAME:" + Mud_name() +
		"||PORTUDP:" + udp_port() +
		"||MSG:" + msg + "@@@\n"
	);
	return 1;
}


//收到信息
void incoming_request(mapping info)
{
	mapping minfo = DNS_MASTER->query_mud_info(info["NAME"]);
	string file, fun;
	
	if(sscanf(info["MSG"], "%s->%s", file, fun) != 2) return;

	if(file_size(IMUD_DIR + file + ".c") > 0)
		(IMUD_DIR + file)->invoke(fun);
}





#endif
