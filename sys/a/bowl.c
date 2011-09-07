
inherit ITEM;
inherit F_SAVE;

#include <ansi.h> 
#include "stock.h"

#define CAPACITY			500			//最大容量

void create ()
{
	set_name(HIW"聚宝盆"NOR, ({"jubao pen", "pen"}));

	set("unit", "只");
	set("no_get", 1);
	set("no_give", 1);

	set("long_msg", "一个天神修筑的聚宝盆");
	
	_data["size"] = CAPACITY;

	setup();
}

//物品列表
string long()
{ 
	return search_items(items_data(), 0);
}

void init()
{ 
	object who = this_player();
	if(userp(who)) {
		add_action("do_putin", "putin"); 
		add_action("do_fetch", "fetch");
		add_action("do_search", "search");
	}
	if(!query_temp("loaded")) {
		seteuid(getuid());
		restore();
		set_temp("loaded", 1);
	}
}

string query_save_file()
{
	return make_save_name("bowl", base_name(environment()));
} 