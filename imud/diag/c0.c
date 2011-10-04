// firefox 04/16/2011
// 诊断程序

#include <imud.h>

inherit F_iEFUN;
inherit F_iCLIENT;
inherit F_CLEAN_UP;


void create()
{
	client_create(([]));
}

int ping(string arg)
{
	send_req("echo", time());
	return 1;
}

void on_echo(mixed* info, string arg)
{
	object who = player_object(info);
	int t = time() - to_int(arg);

	if(who) tell_object(who, "收到消息间隔：" + t + "\n");

}
