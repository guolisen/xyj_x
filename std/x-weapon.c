// firefox 2011.11
// 可变兵器

#include <weapon.h>
#include <ansi.h>

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
	"sword"		: ({ EDGED,	({ "slash", "slice", "thrust", "pierce" }) }),
	"whip"		: ({ 0,	({ "whip","wave" }) }),
	"unarmed"	: ({ 0, ({ "bash", "crush", "slam" }) }),
]);

///初始化成兵器
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
	set_name("可变武器", ({"x weapon"}));
	set_weight(1);

	set("unit", "把");
	
	set("no_sell", 1);
	set("no_stock", 1);

	set("long", "一把可以随意变化的兵器。\n");


	init_type("stick", 60);
	setup();
}

void init()
{
	add_action("do_transform", "transform");
}

static mapping _weapons = ([
	"axe"		: ({ "铁斧", ({ "tie fu", "axe" }), "把" }),
	"blade"		: ({ "钢刀", ({ "gang dao", "blade" }), "把" }),
	"dagger"	: ({ "匕首",	({ "bi shou", "dagger" }), "把" }),
	"fork"		: ({ "钢叉",	({ "gang cha", "fork" }), "柄" }),
	"hammer"	: ({ "铁锤",	({ "tie chui", "hammer", "柄" }) }),
	"mace"		: ({ "铜锏",	({ "tong jian", "mace", "只" }) }),
	"rake"		: ({ "铁耙",	({ "tie pa", "rake" }), "柄" }),
	"spear"		: ({ "铁枪", ({ "tie qiang", "spear" }), "杆" }),
	"staff"		: ({ "铁杖",	({ "tie zhang", "staff" }), "根" }),
	"stick"		: ({ "铁棍",	({ "tie gun", "stick" }), "根" }),
	"sword"		: ({ "铁剑",	({ "tie jian", "sword" }), "柄" }),
	"whip"		: ({ "皮鞭",	({ "pi bian","whip" }), "条" }),
]);

///变成其他兵器
int do_transform(string arg)
{
	mixed* info = _infos[arg];
	mixed* arr = _weapons[arg];
	ojbect who = this_player();
	object weapon = who->query_temp("weapon");
	string name;
	
	if(!info) return notify_fail("要把武器变成什么？\n");
	if(weapon != this_object()) return notify_fail("只能变化主手武器。\n");
	
	name = name();
	unequip();
	
	init_type(arg, 30, 0);
	set_name(arr[0], arr[1]);
	set("unit", arr[2]);

	wield();
	message_vision(CYN"$N对着手中" + name + "吹了口气变作" + name() + "。\n"NOR, who);
	who->reset_action();
	return 1;
}
