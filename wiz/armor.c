// by firefox 11/21/2009

#include <armor.h>
#include <ansi.h>
inherit ARMOR;

void create()
{
	set_name(HIY"���ʥ��"NOR, ({ "golden armor", "armor"}));
	set_weight(100);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ����ӲӵĿ��ף�\n");

		set("material", "iron");
		set("armor_prop/armor", 600);
		set("armor_prop/dodge", 100);

	}
	setup();
}
