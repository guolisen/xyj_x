// by firefox 03/21/2009

#include <armor.h>
inherit NECK;

void create()
{
	set_name("玉佩", ({"yu pei"}));
	set_weight(800);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "个");
		set("value", 2000);
		set("long", "一枚玉佩，刻着一行字：莹莹碧玉魂牵绕，幽幽情思梦相招。\n");
		set("no_sell", 1);
		set("material", "steel");
		set("armor_prop/spells", 30);

	}
	setup();
}

