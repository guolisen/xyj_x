
inherit ITEM;

#include <ansi.h>

#define PROP		"holiday/gift"

void create()
{
	set_name(HIR"����"NOR, ({"hongfeng dai", "dai"}) );
	set_weight(10);
	seteuid(getuid());

	if (clonep())
		set_default_object(__FILE__);
	else {
		set("no_drop", 1);
		set("unit", "��");
		set("long", "�����ഫ���Ƴ����֡���֪����װ��ʲô����(open)�������ɡ�\n");
	}
	setup();
}


void init()
{
	add_action("do_open", ({ "open" }) );
}


int do_open(string arg)
{
	object who = this_player();
	object me = this_object();
	object ob;

	if (arg != "hongfeng dai" && arg != "dai")  return 0;
		
	message_vision("$N��һ������������һ����Ʊ��\n", who);

	ob = new("/obj/money/thousand-cash");
	ob->set_amount(30 + random(11));
	ob->move(who);

	me->move("/obj/empty");
	destruct(me);
	return 1;
}

