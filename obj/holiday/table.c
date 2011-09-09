
inherit ITEM;

#include <ansi.h>

string _food = __DIR__"food";

void create()
{
	set_name("������", ({"baxian zhuo", "zhuo", "table"}));
	set_weight(5000000);

	seteuid(getuid());	

	if(clonep())
		set_default_object(__FILE__);
	else 
	{
		set("unit", "��");
		set("no_get",1);
		set("long", "��������ζ(food)���˴������ߣ�ʱ��������(pick)һ�顣\n");
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
		return notify_fail("��Ҫ��ʲô��\n");
	else if(_food->eaten())
		return notify_fail("���Ѿ��Թ��ˣ���������˰ɡ�\n");
	else {
		object ob = new(_food);
		if(ob->move(who)) {
			message_vision("$N������������һ��$n��\n", who, ob);
		} else {
			destruct(ob);
			tell_object(who, "��Я���Ķ���̫���ˡ�\n");
		}
	}
	return 1;

}