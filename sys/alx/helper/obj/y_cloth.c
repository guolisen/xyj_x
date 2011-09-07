// by firefox 11/21/2009

#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
	set_name(HIY"ÐÓ»ÆÅÛ"NOR, ({ "cloth" }));
	set_weight(1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "cloth");
		set("unit", "¼þ");
		set("armor_prop/armor", 1);

		//set("no_get", 1);
	}
	setup();
}
