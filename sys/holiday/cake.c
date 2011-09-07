
inherit ITEM;

#include <ansi.h>

#define PROP		"holiday/food"

void create()
{
	set_name(YEL"����"NOR, ({"hu bing", "bing"}) );
	set_weight(10);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("no_drop", 1);
		set("unit", "��");
		set("long", "��ζ�ĺ�����ǡʼ�ڵ���(�Ƴ�)����������������Բ��\n");
	}

	setup();
}


void init()
{
	add_action("do_eat", ({ "eat", "chi" }) );
}


int do_eat(string arg)
{
	object who = this_player();
	object me = this_object();

	if (arg != "hu bing" && arg != "bing")  return 0;

	if(who->query(PROP)) {
		message_vision("$Nһ�ڽ��������£���ͬ��˽���˲ι���û������ζ��\n", who);
	} else {
		who->set(PROP, 20101001);
		message_vision("$N�������ϸϸƷζ����ʱ�������㡣\n", who);
		tell_object(who, "��о�������Ϊ�����ˣ�ͬʱ�����彡��\n");

		who->add("potential", 50000);

		who->add_maximum_force(200);
		who->add_maximum_mana(200);
		who->add("rsg_eaten", 5);
	}

	who->set("food", who->max_food_capacity());
	who->set("water", who->max_water_capacity());
	
	me->move("/obj/empty");
	destruct(me);
	return 1;
}

