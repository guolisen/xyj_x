// by firefox 11/21/2009

#include <weapon.h>
#include <ansi.h>
inherit MACE;

string* names = ({"�����װ�", "�����װ�"});

void create()
{
	set_name(HIY + names[random(2)] + NOR, ({"mace"}));
	set_weight(1000);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "iron");
		set("long", "һ�������õĻ���ﵡ�\n");
	}
	init_mace(1);

	setup();
}

