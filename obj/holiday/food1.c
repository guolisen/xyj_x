
inherit ITEM;

#include <xyj_x.h>
#include <ansi.h>

#define PROP		"gift/holiday"

#define DATE		20110101
#define POT			60000

#define NAME		"����"
#define ID			"hu rou"
#define LONG		"һ����ζ�ĺ��⣬��˵ȡ����һ�ֺ����Ļ����"

string* _prefixs = ({"����", "����", "����", "����", "�罷", ""});

void create()
{
	set_name(random1(_prefixs) + NAME, ({ID, "food"}));
	set_weight(0);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("no_drop", 1);
		set("unit", "��");
		set("long", LONG + "\n");
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

	if (arg != me->query("id") && arg != "food")  return 0;

	if(who->query(PROP) < DATE) {
		who->set(PROP, DATE);
		message_vision("$N����$nϸϸƷζ���о���ζ���\n", who, me);
		who->add("potential", POT);
	} else {
		message_vision("$Nһ������$n����ͬ��˽���˲ι���û������ζ��\n", who, me);
	}

	who->set("food", who->max_food_capacity());
	who->set("water", who->max_water_capacity());
	
	destruct(me);
	return 1;
}



