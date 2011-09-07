// by firefox 11/21/2009

#include <weapon.h>
#include <ansi.h>
inherit MACE;

string* names = ({"四棱金装锏", "瓦面金装锏"});

void create()
{
	set_name(HIY + names[random(2)] + NOR, ({"mace"}));
	set_weight(1000);

	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "根");
		set("material", "iron");
		set("long", "一柄金光灿烂的护手锏。\n");
	}
	init_mace(1);

	setup();
}

