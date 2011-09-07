
inherit ITEM;

#include <ansi.h> 
#include "stock.h"

#define DATA						"stock/bag"

string query_autoload() { return ""; }
void autoload(string param) {}

void create ()
{
	set_name("�����", ({"ruyi dai", "dai"}));

	set("unit", "ֻ");
	set("no_get", 1);
	set("no_give", 1);
	set("no_break", 1);

	set("long_msg", "����һ����������Ĵ���");

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
			who->set_temp(DATA, me);	//��¼ĳ�˵Ĵ��ӣ����㶪ʧʱ����
			return;
		}
	}
	call_out("destruct_me", 1, env, me);
}

void destruct_me(object env, object me)
{
	//message_vision("$N���ϵ�$n��ʧ�ˡ�\n", env, me);
	if(me) destruct2(me);
}

//��ȡ��ұ�������
mapping query_data()
{
	object who = this_player();
	if(who) {
		if(!who->query(DATA"/items")) who->set(DATA"/items", ({}));
		return who->query(DATA);
	}
	return 0;
}