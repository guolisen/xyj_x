// firefox 2011.11.11
// 百变armor

#include <armor.h>

inherit EQUIP;


mapping _infos = ([
	TYPE_HEAD
	TYPE_NECK
	TYPE_CLOTH
	TYPE_ARMOR
	TYPE_SURCOAT
	TYPE_WAIST
	TYPE_WRISTS
	TYPE_SHIELD
	TYPE_FINGER
	TYPE_HANDS
	TYPE_BOOTS

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
	set_name("X装备", ({ "x armor" }) );
	set_weight(1);

	set("unit", "件");
	
	set("no_sell", 1);
	set("no_stock", 1);
	set("armor_prop/armor", 30);

	set("long", "一把可以随时变化的兵器。\n");

	setup();
}


