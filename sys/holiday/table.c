
inherit ITEM;

#include <ansi.h>

void create()
{
	set_name("������", ({"baxian zhuo", "zhuo", "table"}));
	set_weight(5000000);

	seteuid(getuid());	

	if( clonep() )
		set_default_object(__FILE__);
	else 
	{
		set("unit", "��");
		set("no_get",1);
		set("long", "�����϶����˺���(hu bing)��ʱ��������(pick)һ�顣\n");
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
		return notify_fail("����ʲô������ֻ�к���(hu bing)��\n");
	else {
		object ob = new(__DIR__"cake");
		if(ob->move(who)) {
			message_vision("$N������������һ�������\n", who);
		} else {
			destruct(ob);
			tell_object(who, "��Я���Ķ���̫���ˡ�\n");
		}
	}
	return 1;

}

