
inherit ITEM;

#include <ansi.h> 
#include "stock.h"

#define DATA						"stock/bag"

string query_autoload() { return ""; }
void autoload(string param) {}

void create ()
{
	set_name("如意袋", ({"ruyi dai", "dai"}));

	set("unit", "只");
	set("no_get", 1);
	set("no_give", 1);
	set("no_break", 1);

	set("long_msg", "这是一个轻若无物的袋子");

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
	object me = this_object();
	object who = this_player();
	object env = environment();

	if(who != env) return;
	if(userp(who)) {
		object bag = who->query_temp(DATA);
		if(bag && environment(bag) != who) destruct2(bag);

		if(!query("owner")) set("owner", getuid(who));

		if(!bag && query("owner") == getuid(who)) {
			add_action("do_putin", "putin"); 
			add_action("do_fetch", "fetch");
			//add_action("do_search", "search");
			who->set_temp(DATA, me);	//记录某人的袋子，方便丢失时销毁
			return;
		}
	}
	call_out("destruct_me", 1, env, me);
}

void destruct_me(object env, object me)
{
	//message_vision("$N身上的$n消失了。\n", env, me);
	if(me) destruct2(me);
}

//获取玩家背包数据
mapping query_data()
{
	object who = this_player();
	if(who) {
		if(!who->query(DATA"/items")) who->set(DATA"/items", ({}));
		return who->query(DATA);
	}
	return 0;
}