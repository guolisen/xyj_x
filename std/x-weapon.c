// firefox 2011.11
// 可变兵器

#include <weapon.h>

inherit EQUIP;

static mapping _infos = ([
	"axe"		: ({ EDGED, ({ "chop", "slice", "hack" }) }),
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
	set_name("降魔棒", ({"xiangmo bang", "bang"}));
	set_weight(8000);

	set("unit", "把");
	set("no_sell", 1);
	set("long", "一把淡青色的短棒，上面有暗红流动，如同一条火蛇般绕在棒上。\n");
	set("value", 20000);
	set("material", "steel");
	set("wield_msg", "$N「呼」地一声抽出一把$n握在手中。\n");

	init_type("stick", 60);
	setup();
}

void init()
{
	add_action("do_transform", "transform");
}

int do_transform(string arg)
{
	mixed* info = _infos[arg];
	if(!info) return notify_fail("要把武器变成什么？\n");

	init_type(arg, 100, 0);
}