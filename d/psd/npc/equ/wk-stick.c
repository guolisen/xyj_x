// by firefox 11/21/2009

#include <weapon.h>
#include <ansi.h>
inherit STICK;

void create()
{
	set_name(HIY"����𹿰�"NOR, ({"golden stick", "stick"}));
	set_weight(1000000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
//		set("long", "����һ�ѳ�ǹ��ͨ���̽�\n");
		set("material", "iron");
		//set("wield_msg","$N�ó�һ��$n���������У�\n");
		//set("unwield_msg", "$N�������е�$n��\n");

		set("no_get", 1);
	}
	init_stick(250);
	setup();
}
