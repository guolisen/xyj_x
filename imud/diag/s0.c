// firefox 04/16/2011
// ��ϳ���

#include <imud.h>

inherit F_iEFUN;
inherit F_iSERVER;
inherit F_CLEAN_UP;


void create()
{
	server_create();
}

int echo(mixed* info, string str)
{
	notify_all("on_echo", info, str);

	ICE_D->flush();
	return 1;
}
