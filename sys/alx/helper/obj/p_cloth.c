// by firefox 11/21/2009

#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
	set_name(HIC"猪之战甲"NOR, ({ "zhuzhi zhanjia" }));
	set_weight(1);
	if( clonep() )
		set_default_object(__FILE__);
	else {		
		set("long", "一件猪赐的护甲，据说它的能力不会随主人成长。\n");
		set("material", "cloth");
		set("unit", "件");
		set("armor_prop/armor", 20);
		set("no_stock", 1);
	}
	setup();
}
