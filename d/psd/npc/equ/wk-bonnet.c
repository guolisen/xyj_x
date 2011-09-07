// by firefox 11/21/2009

#include <armor.h>
#include <ansi.h>
inherit HEAD;

void create()
{
	set_name(MAG"×Ï½ð¹Ú"NOR, ({ "purple bonnet", "bonnet"}) );
	set_weight(1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "¶¥");
		set("material", "steel");

		set("armor_prop/armor", 1);

		//set("no_get", 1);
	}
	setup();
}

