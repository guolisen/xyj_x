#ifndef I_ICE_H_INCLUDED
#define I_ICE_H_INCLUDED
// by firefox 04/16/2011


#include <net/dns.h>
#include <net/macros.h>
#include <net/daemons.h>

inherit F_CLEAN_UP;
inherit F_DBASE;



/*

ice	ͨѶ�м��������������Ϣ���ݡ�Ӧ���и����ģ�������³���ȵȡ�


������Ϣ���ǹ㲥���ܵ�����Ϣ����������������ת���������ѷ���������Ϣ��NxN����Ϣ��


1.�������������������ӵ�ĳ��������
2.�õ��������ϵ�Ӧ���������ӳɹ���
3.ĳ���������ߣ�ս����ֹ��
4.ÿ��gameȷ��һ������������
5.��ΪȨ��ԭ��ice�������ȶ������ܳ����¡�


����ɱ��û�п�̨���ڡ�


��ս
	���գ����ˡ�


��Ϸ�������̣�
1.����㲥��
2.Ӧ�𳬹���������Ϸ������
3.��һ�ֳ�ʼ����Ϣ����������ӵȵȡ�
4.��ʼ��Ϣ�غ�
5.������ֹͣ��Ϸ����


1.�ĳ���һ�ַ�����һ�غ�
2.����ɱ��һ����Ҳ�����һ�غ�
3.��ս��һ�ֳ�����һ�غ�
*/


mapping _mudlist = ([
	"xyj-cn"		: ([
		"name"			: "���μ�����վ",
		"ip"			: ({"221.238.143.29", "60.28.50.88"}),
		"udpport"		: 2012,
	]),
	"xyj-tj"		: ([
		"name"			: "���μ����վ",
		"ip"			: ({"221.238.143.30", "60.28.50.54"}),
		"udpport"		: 6670,
	])
]);



//������Ϣ
int send_msg(string mud, string msg)
{
	mapping minfo = DNS_MASTER->query_mud_info(mud);

	if(!minfo) return 0;		//������δ��ͨ
	
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


//�յ���Ϣ
void incoming_request(mapping info)
{
	mapping minfo = DNS_MASTER->query_mud_info(info["NAME"]);


	fcs/s0.join(���:firefox:xyj-cn) 
	fcs/s0.bet(firefox@xyj-cn,n) 
	fcs/c0.on_bet(���:firefox:xyj-cn:n,pot+���:firefox:xyj-cn:20+) 
		,

	mapping minfo, mudinfo;
	object pl;
	string reply;

	if (info["NAME"] && info["PORTUDP"]) {
		// dont want to tell to ourselves
		if (info["NAME"] == Mud_name())	return;

		// get our info about the sender, ping them if we don't have any		
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
		tell_object(ob, HIG + info["WIZFROM"]+"֪ͨ�㣺"+info["MSG"] + NOR);
	}
}


#endif