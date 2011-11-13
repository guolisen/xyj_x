// firefox 2011.11.11
// 百变armor

#include <armor.h>

inherit EQUIP;


mapping _infos = ([
	TYPE_ARMOR		: ({ EDGED, ({ "chop", "slice", "hack" }) }),
	"blade"		: ({ EDGED, ({ "slash", "slice", "hack", "chop" }) }),
	"dagger"	: ({ EDGED | SECONDARY,	({ "pierce", "thrust" }) }),
	"fork"		: ({ POINTED,	({ "pierce", "thrust" }) }),
	"hammer"	: ({ 0,	({ "bash", "crush", "slam" }) }),
	"mace"		: ({ 0,	({ "impale", "bash", "crush", "slam" }) }),
	"rake"		: ({ EDGED,	({ "rake", "strike", "bash" }) }),
	"spear"		: ({ POINTED, ({ "thrust", "impale", "pierce" }) }),
	"staff"		: ({ LONG,	({ "bash", "crush", "slam", "pierce", "impale" }) }),
	"stick"		: ({ LONG,	({ "bash", "crush", "slam" }) }),
	"swork"		: ({ EDGED,	({ "slash", "slice", "thrust", "pierce" }) }),
	"whip"		: ({ 0,	({ "whip","wave" }) }),
	"mace"		: ({ 0,	({ "impale", "bash", "crush", "slam" }) }),
	"unarmed"	: ({ 0, ({ "bash", "crush", "slam" }) }),

]);



void setup(string type)
{
	set("armor_type", type);
	if( !query("armor_apply/dodge")
	&&	weight() > 3000 )
		set("armor_prop/dodge", - weight() / 3000 );
}


varargs void init_type(string type, int damage, int flag)
{
	mixed* info = _infos[type];

	set("weapon_prop/damage", damage);
	set("flag", flag | info[0]);
	set("skill_type", type);
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", info[1] );
	}
}



void create()
{
	set_name("天兵战甲", ({ "heaven armor", "armor" }) );
	set_weight(25000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "件");
		set("material", "gold");
		set("value", 4000);
		set("armor_prop/armor", 30);
	}
	setup();
}


