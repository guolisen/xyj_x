
inherit ITEM;

#include <ansi.h> 
#include "stock.h"

#define DATA						"stock/bank"

void create ()
{
	set_name("���д����", ({"chuwu gui", "gui", "box"}));

	set("unit", "ֻ");
	set("no_get", 1);
	set("no_give", 1);
	set("no_break", 1);

	set("long_msg", "���д���񣬿ɼĴ�/��ȡ��Ʒ");

	seteuid(getuid());
	
	setup();
}

//��Ʒ�б�
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

//��ȡ������вֿ�����
mapping query_data()
{
	object who = this_player();
	if(who) {
		if(!who->query(DATA"/items")) who->set(DATA"/items", ({}));
		return who->query(DATA);
	}
	return 0;
}