
inherit ITEM;

#include <ansi.h> 
#include "stock.h"

#define DATA						"stock/bank"

void create ()
{
	set_name("银行储物柜", ({"chuwu gui", "gui", "box"}));

	set("unit", "只");
	set("no_get", 1);
	set("no_give", 1);
	set("no_break", 1);

	set("long_msg", "银行储物柜，可寄存/领取物品");

	seteuid(getuid());
	
	setup();
}

//物品列表
string long()
{ 
	return search_items(items_data(), 0);
}

void init()
{ 
	add_action("do_putin", "jicun"); 
	add_action("do_fetch", "lingqu");
	//add_action("do_search", "search");
}

//获取玩家银行仓库数据
mapping query_data()
{
	object who = this_player();
	if(who) {
		if(!who->query(DATA"/items")) who->set(DATA"/items", ({}));
		return who->query(DATA);
	}
	return 0;
}