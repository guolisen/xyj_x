
inherit ITEM;

#include <ansi.h>

string _food = __DIR__"food";

void create()
{
	set_name("八仙桌", ({"baxian zhuo", "zhuo", "table"}));
	set_weight(5000000);

	seteuid(getuid());	

	if(clonep())
		set_default_object(__FILE__);
	else 
	{
		set("unit", "个");
		set("no_get",1);
		set("long", "桌子上美味(food)让人垂涎三尺，时常有人拿(pick)一块。\n");
		set("value", 1);
	}
}

void init()
{
	add_action("do_pick", "pick");
}

int do_pick(string arg)
{
	object who = this_player();

	if (arg != "food")
		return notify_fail("你要拿什么？\n");
	else if(_food->eaten())
		return notify_fail("你已经吃过了，留点给别人吧。\n");
	else {
		object ob = new(_food);
		if(ob->move(who)) {
			message_vision("$N从桌子上拿起一块$n。\n", who, ob);
		} else {
			destruct(ob);
			tell_object(who, "你携带的东西太多了。\n");
		}
	}
	return 1;

}