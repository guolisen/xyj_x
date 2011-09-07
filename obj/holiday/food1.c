
inherit ITEM;

#include <xyj_x.h>
#include <ansi.h>

#define PROP		"gift/holiday"

#define DATE		20110101
#define POT			60000

#define NAME		"狐肉"
#define ID			"hu rou"
#define LONG		"一块美味的狐肉，据说取材自一种罕见的火狐。"

string* _prefixs = ({"红烧", "清蒸", "椒盐", "白灼", "剁椒", ""});

void create()
{
	set_name(random1(_prefixs) + NAME, ({ID, "food"}));
	set_weight(0);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("no_drop", 1);
		set("unit", "块");
		set("long", LONG + "\n");
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

	if (arg != me->query("id") && arg != "food")  return 0;

	if(who->query(PROP) < DATE) {
		who->set(PROP, DATE);
		message_vision("$N拿起$n细细品味，感觉回味无穷。\n", who, me);
		who->add("potential", POT);
	} else {
		message_vision("$N一口吞下$n，如同猪八戒吃人参果，没尝出滋味。\n", who, me);
	}

	who->set("food", who->max_food_capacity());
	who->set("water", who->max_water_capacity());
	
	destruct(me);
	return 1;
}



