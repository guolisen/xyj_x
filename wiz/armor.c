// by firefox 11/21/2009

#include <armor.h>
#include <ansi.h>
inherit ARMOR;

void create()
{
	set_name(HIY"金甲圣衣"NOR, ({ "golden armor", "armor"}));
	set_weight(100);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "件");
		set("long", "一件金灿灿的盔甲．\n");

		set("material", "iron");
		set("armor_prop/armor", 600);
		set("armor_prop/dodge", 100);

	}
	setup();
}
