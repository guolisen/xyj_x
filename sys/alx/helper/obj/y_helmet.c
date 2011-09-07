// by firefox 11/21/2009

#include <armor.h>
#include <ansi.h>
inherit HEAD;

void create()
{
	set_name(HIY"飞龙闹珠金盔"NOR, ({ "dragon helmet", "helmet"}) );
	set_weight(1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "顶");
		set("material", "steel");
		set("long", "一顶结实的金盔。\n");

		set("armor_prop/armor", 1);

		//set("no_get", 1);
	}
	setup();
}

