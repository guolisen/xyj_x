// firefox 2011.11.11
// 百变armor

#include <armor.h>

inherit EQUIP;

/*
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
*/

///初始化一个类型
void init_type(string type, int armor)
{
	set("armor_type", type);
	if(!query("armor_apply/dodge") && weight() > 3000)
		set("armor_prop/dodge", -weight() / 3000);
	set("armor_prop/armor", armor);
}

///造假
void make_fake(object ob)
{
	int armor = 1 + ob->query("armor_prop/armor") / 2;

	set_name(ob->query("name"), ob->query_my_id());
	init_type(ob->query("armor_type"), armor);
	set("unit", ob->query("unit"));

	set("no_get", 1);
	set("no_stock", 1);
	set("no_give", 1);
}

void create()
{
	set_name("X装备", ({ "x armor" }) );
	set_weight(1);

	set("unit", "件");
	set("long", "一把可以随时变化的兵器。\n");

	init_type(TYPE_ARMOR, 30);
}


void init()
{
//	add_action("do_transform", "transform");
	add_action("do_test", "test");
}

int do_test()
{
	make_fake(this_player()->query_temp("armor/armor"));
}
