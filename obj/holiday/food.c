
inherit ITEM;

#include <xyj_x.h>
#include <ansi.h>

#define PROP		"gift/holiday"

#define DATE		20110606
#define POT			30000

#define NAME		""
//#define ID			"mang guo"
//#define LONG		"太忙了，祝大家吃得开心，玩得愉快。"
//string* _prefixs = ({"芒果", "芒果"});

//#define LONG		"愿MUD西游记一年更比一年红火。"

#define ID			"zong zi"
#define LONG		"四时花竞巧，九子粽争新。祝大家端午愉快。"
string* _prefixs = ({"粽子", "粽子"});

void create()
{
	set_name(random1(_prefixs) + NAME, ({ID, "food"}));
	set_weight(0);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("no_drop", 1);
		set("unit", "个");
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



