// by firefox 11/12/2010

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"gift";

void create()
{
	set_name(HIY"����"NOR, ({"huan dan" }));
	
	set("long", "���ҺϾ�ת������ɰ�ٴ��������ɵ��ɵ���\n\n");
	set("rewards", ([ DEXP : 100*K ]));
	set("eat_msg", "$N����һ��$n���پ�ƮƮ���ɡ�\n\n");

	setup();
}

