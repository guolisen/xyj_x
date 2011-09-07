
inherit ITEM;

#include <ansi.h>

#define PROP		"holiday/food"

void create()
{
	set_name(YEL"胡饼"NOR, ({"hu bing", "bing"}) );
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("no_drop", 1);
		set("unit", "块");
		set("long", "美味的胡饼，恰始于当代(唐初)，象征着美满和团圆。\n");
	}

	setup();
}


void init()
{
	add_action("do_eat", ({ "eat", "chi" }) );
}


int do_eat(string arg)
{
	object who = this_player();
	object me = this_object();

	if (arg != "hu bing" && arg != "bing")  return 0;

	if(who->query(PROP)) {
		message_vision("$N一口将胡饼吞下，如同猪八戒吃人参果，没尝出滋味。\n", who);
	} else {
		who->set(PROP, 20101001);
		message_vision("$N拿起胡饼细细品味，顿时唇齿留香。\n", who);
		tell_object(who, "你感觉自身修为加深了，同时身轻体健。\n");

		who->add("potential", 50000);

		who->add_maximum_force(200);
		who->add_maximum_mana(200);
		who->add("rsg_eaten", 5);
	}

	who->set("food", who->max_food_capacity());
	who->set("water", who->max_water_capacity());
	
	me->move("/obj/empty");
	destruct(me);
	return 1;
}

