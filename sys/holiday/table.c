
inherit ITEM;

#include <ansi.h>

void create()
{
	set_name("八仙桌", ({"baxian zhuo", "zhuo", "table"}));
	set_weight(5000000);

	seteuid(getuid());	

	if( clonep() )
		set_default_object(__FILE__);
	else 
	{
		set("unit", "个");
		set("no_get",1);
		set("long", "桌子上堆满了胡饼(hu bing)，时常有人拿(pick)一块。\n");
		set("value", 1);
	}
}

void init()
{
	add_action("do_pick","pick");
}

int do_pick(string arg)
{
	object who = this_player();

	if (arg != "hu bing" &&  arg != "bing")
		return notify_fail("你拿什么？桌上只有胡饼(hu bing)。\n");
	else {
		object ob = new(__DIR__"cake");
		if(ob->move(who)) {
			message_vision("$N从桌子上拿起一块胡饼。\n", who);
		} else {
			destruct(ob);
			tell_object(who, "你携带的东西太多了。\n");
		}
	}
	return 1;

}

