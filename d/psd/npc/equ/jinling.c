
#include <armor.h>
#include <ansi.h>

inherit HANDS;

void create()
{
	set_name(HIY"银索金玲"NOR, ({"yinsuo jinling", "jinling", "ling"}));
	set_weight(80);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "个");
		set("value", 2000);
		set("long", "一枚玉佩，上面还刻着一些图案．\n");
		set("no_sell", 1);
		set("material", "steel");
		set("armor_prop/spells", 5);
		set("armor_prop/armor", 1);

	}
	setup();
}

