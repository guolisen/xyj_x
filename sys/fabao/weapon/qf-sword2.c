// by firefox 03/21/2009

#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
	set_name("青锋剑", ({ "qingfeng sword", "sword" }) );
	set_weight(640);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("material", "steel");
		set("long", "青锋雄剑，色程淡青，灵动锋利。\n");
		//set("wield_msg", "$N抽出$n握在手中，好似凤舞九天。\n");
		//set("unwield_msg", "$N把$n插入剑鞘，光华顿收。\n");
	}
	init_dagger(20);
	setup();
}
