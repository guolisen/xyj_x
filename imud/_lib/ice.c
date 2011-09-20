#ifndef I_ICE_H_INCLUDED
#define I_ICE_H_INCLUDED
// by firefox 04/16/2011


/*

ice	通讯中间件，服务器间消息传递。应该有个中心，负责更新程序等等。


所有消息都是广播？受到的消息，都像其他服务器转发，除非已发出过该消息。NxN条消息？


1.像其他服务器请求连接到某公共对象。
2.得到半数以上的应答算作连接成功。
3.某服务器掉线，战斗终止。
4.每个game确定一组参与服务器。
5.因为权限原因ice，尽量稳定，不能常更新。


西游杀，没有看台观众。


海战
	船舱，本人。


游戏启动流程：
1.请求广播。
2.应答超过半数，游戏建立。
3.第一轮初始化消息。随机数种子等等。
4.开始消息回合
5.结束，停止游戏对象。


1.赌场：一轮发牌是一回合
2.西游杀：一个玩家操作是一回合
3.海战：一轮出手是一回合
*/



void send_gtell(string mud, string wiz_to, object source, string msg)
{
	mapping minfo;

	if(!ACCESS_CHECK(previous_object())
	&&	base_name(previous_object()) != TELL_CMD) return;

	mud = htonn( mud );

	if(mud == mud_nname() || !geteuid(source)) return;

	minfo = (mapping)DNS_MASTER->query_mud_info(mud);
	if (!minfo) return ;

	msg = replace_string(msg, "|", "");
	msg = replace_string(msg, "@@@", "");
	DNS_MASTER->send_udp(minfo["HOSTADDRESS"], minfo["PORTUDP"],
		"@@@" + DNS_GTELL +
		"||NAME:" + Mud_name() +
		"||PORTUDP:" + udp_port() +
		"||WIZTO:" + wiz_to +
		"||WIZFROM:" + capitalize(geteuid(source)) +
		"||CNAME:" + source->name(1) +
		"||MSG:"+msg+"@@@\n");
}

// Someone on another mud has sent us a tell.
void incoming_request(mapping info)
{
	mapping minfo, mudinfo;
	object pl;
	string reply;

	if (info["NAME"] && info["PORTUDP"]) {
		// dont want to tell to ourselves
		if (info["NAME"] == Mud_name())	return;

		// get our info about the sender, ping them if we don't have any
		minfo = DNS_MASTER->query_mud_info(info["NAME"]);
		if (!minfo || !DNS_MASTER->dns_mudp(info["NAME"]))
			PING_Q->send_ping_q(info["HOSTADDRESS"], info["PORTUDP"]);

		if (minfo && minfo["HOSTADDRESS"] != info["HOSTADDRESS"]) {
			// Its been faked! 
			dns_log("dns_fake", "Tell: "+info["WIZFROM"]+"@"+info["NAME"]+
				"("+info["HOSTADDRESS"]+") telling "+info["WIZTO"]
				+" "+ info["MSG"]+"\n");
			DNS_MASTER->send_udp(minfo["HOSTADDRESS"], minfo["PORTUDP"],
				"@@@"+DNS_WARNING+
				"||MSG: Faked gtell message "+info["WIZFROM"]+
				"@"+info["NAME"]+"> "+info["WIZTO"]+
				" "+info["MSG"]+
				"||FAKEHOST:"+info["name"]+
				"@@@\n");
			return ;
		}

	        reply=TELL_CMD->remote_tell( info["CNAME"], info["WIZFROM"], 
		    info["NAME"], info["WIZTO"], info["MSG"]);
                
		mudinfo=DNS_MASTER->query_mud_info(Mud_name());
		// query info about ourselves.

		(AUX_PATH+"affirmation_a")->send_affirmation_a(info["HOSTADDRESS"],
			info["PORTUDP"], 
			mudinfo["MUDNAME"], //"Gtell@"+Mud_name(),
			info["WIZFROM"], reply, "gtell");
	} //if (info["NAME"] && info["PORTUDP"])
}



void incoming_request(mapping info)
{
	object ob;

	if(!ACCESS_CHECK(previous_object())) return;

	if (!info["NAME"] || info["NAME"] == Mud_name()) return;

	if (info["WIZTO"]) {
		if( info["MSG"][sizeof(info["MSG"])] != '\n' ) info["MSG"] += "\n";
		if (ob = find_player(lower_case(info["WIZTO"])))
		tell_object(ob, HIG + info["WIZFROM"]+"通知你："+info["MSG"] + NOR);
	}
}


#endif