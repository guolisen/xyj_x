// by firefox 11/12/2010

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"gift";

void create()
{
	set_name(YEL"��ת��"NOR, ({"jiuzhuan jindan", "jindan" }));
	
	set("long", "Ӧ��ʱ����ȡҩ�����ת���������ɡ�\n\n");
	set("rewards", ([ DEXP : 10*K ]));
	set("eat_msg", "$N����һ��$n���پ�ƮƮ���ɡ�\n\n");

	setup();
}

