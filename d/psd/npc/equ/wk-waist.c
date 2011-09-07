// by firefox 11/21/2009

#include <armor.h>
#include <ansi.h>
inherit WAIST;

void create()
{
	set_name(HIW"À¶Ìï´ø"NOR, ({"jade belt", "belt", "dai"}));
	set_weight(1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "¼þ");

		set("material", "metal");

		set("armor_prop/armor", 1);
		set("armor_prop/dodge", 1);
	}
	setup();
}
