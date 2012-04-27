// firefox 11/21/2009

#include <armor.h>
#include <ansi.h>

inherit FINGER;

void create()
{
	set_name(YEL"±¶µÒπ≠"NOR, ({"bow" }) );
	set_weight(1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "’≈");
		set("material", "steel");

		set("armor_prop/armor", 1);

		//set("no_get", 1);
	}
	setup();
}
