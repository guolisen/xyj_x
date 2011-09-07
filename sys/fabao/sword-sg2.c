// by firefox 03/21/2009

#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
	set_name("双股剑", ({ "ci sword", "sword" }) );
	set_weight(640);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("material", "steel");
		set("long", "双股雌剑，东汉先秦制式，柄饰浴火凤凰，长三尺四寸，重六斤四两。\n");
		set("wield_msg", "$N抽出$n握在手中，好似凤舞九天。\n");
		//set("unwield_msg", "$N把$n插入剑鞘，光华顿收。\n");
	}
	init_dagger(20);
	setup();
}
