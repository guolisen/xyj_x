
inherit ITEM;
inherit F_SAVE;

#include <ansi.h> 
#include "stock.h"

#define CAPACITY			500			//�������

void create ()
{
	set_name(HIW"�۱���"NOR, ({"jubao pen", "pen"}));

	set("unit", "ֻ");
	set("no_get", 1);
	set("no_give", 1);

	set("long_msg", "һ�����������ľ۱���");
	
	_data["size"] = CAPACITY;

	setup();
}

//��Ʒ�б�
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