// by firefox 11/21/2009

#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
	set_name(WHT"死猪的魔爪"NOR, ({"deathtouch" }) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long", "一柄灰色的利刃。\n");
		set("value", 55);
		set("material", "steel");
	}
	init_dagger(40);

	set("wield_msg", "$N从怀中摸出一把$n握在手中。\n");
	set("unwield_msg", "$N将手中的$n藏入怀中。\n");

	setup();
}
