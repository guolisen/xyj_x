// by firefox 11/21/2009

#include <armor.h>
#include <ansi.h>
inherit HANDS;

void create()
{
	set_name(HIY"������"NOR, ({"jian hu"}));
	set_weight(1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("material", "metal");
		set("armor_prop/armor", 1);
	}
	setup();
}
