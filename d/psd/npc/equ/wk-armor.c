// by firefox 11/21/2009

#include <armor.h>
#include <ansi.h>
inherit ARMOR;

void create()
{
	set_name(HIY"���ʥ��"NOR, ({ "golden armor", "armor"}));
	set_weight(1000000);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ����ӲӵĿ��ף�\n");

		set("material", "iron");
		set("armor_prop/armor", 1000);
		set("armor_prop/dodge", 1);

		set("no_get", 1);
	}
	setup();
}
