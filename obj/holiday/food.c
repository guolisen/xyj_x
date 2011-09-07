
inherit ITEM;

#include <xyj_x.h>
#include <ansi.h>

#define PROP		"gift/holiday"

#define DATE		20110606
#define POT			30000

#define NAME		""
//#define ID			"mang guo"
//#define LONG		"̫æ�ˣ�ף��ҳԵÿ��ģ������졣"
//string* _prefixs = ({"â��", "â��"});

//#define LONG		"ԸMUD���μ�һ�����һ����"

#define ID			"zong zi"
#define LONG		"��ʱ�����ɣ����������¡�ף��Ҷ�����졣"
string* _prefixs = ({"����", "����"});

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



