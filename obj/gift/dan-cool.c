// by firefox 11/12/2010

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"gift";


string eat_msg()
{
	_player->add("bellicosity", -10);
	
	return "$N����һ��$n�����Ͻ���һ��˪��\n\n";
}

void create()
{
	set_name(HIW"��ˮ����"NOR, ({"bishui huandan", "handan"}));
	
	set("long", "һ��ð�ź����ĵ�ҩ����˵��������ˮ���������ɡ�\n\n");
	set("rewards", ([ PEXP : 25*K ]));
	set("eat_msg", (: eat_msg :));

	setup();
}

