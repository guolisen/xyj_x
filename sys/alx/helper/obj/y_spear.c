// by firefox 11/21/2009

#include <weapon.h>
#include <ansi.h>
inherit SPEAR;

string* names = ({ "虎头錾金枪", "金攥提龙枪", "八宝驼龙枪" });

void create()
{
	set_name(HIY + names[random(3)] + NOR, ({"spear"}));
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long", "这是一把长枪，通体鎏金。\n");
		set("material", "iron");
		set("no_stock", 1);
	}
	init_spear(40);
	setup();
}
