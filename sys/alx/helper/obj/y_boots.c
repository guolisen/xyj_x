// by firefox 11/21/2009

#include <armor.h>
#include <ansi.h>
inherit BOOTS;

void create()
{
	set_name(YEL"÷äÆ¤Ñ¥"NOR, ({"boots"}));
	set_weight(1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "Ë«");
		set("long","Ò»Ë«Æ¤Ñ¥£¬÷äÆ¤ÖÆ³É¡£\n");
		set("material", "cloth");
		set("armor_prop/armor", 1);

		//set("no_get", 1);
	}
	setup();
}

