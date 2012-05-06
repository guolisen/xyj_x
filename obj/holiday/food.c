
inherit ITEM;

#include <xyj_x.h>
#include <ansi.h>

#define PROP		"gift/holiday"

#define DATE		20120501
#define POT			30000


//#define ID			"mang guo"

//#define LONG		"ԸMUD���μ�һ�����һ����"
//#define LONG		"��ʱ�����ɣ����������¡�ף��Ҷ�����졣"
//#define LONG		"�Ƴ���ʢ�������������±���ף�������/������֡�"

#define NAME		""
#define ID			""
//#define LONG		"Ը��ҽ��տ��֣�ԭMUD���μ�һ�����һ����"
//string* _tab = ({ ({"���", "nian gao"}), ({"����", "jiao zi"}), ({"��Բ", "tang yuan"}) });
#define LONG		"̫æ�ˣ�ף��ҳԵÿ��ģ������졣"
string* _tab = ({ ({"â��", "mang guo"}), });


void create()
{
	string arr = random1(_tab);
	set_name(arr[0] + NAME, ({arr[1] + ID, "food"}));
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

//�Թ���
int eaten()
{
	return this_player()->query(PROP) >= DATE;
}


int do_eat(string arg)
{
	object who = this_player();
	object me = this_object();

	if (arg != me->query("id") && arg != "food")  return 0;

	if(!eaten()) {
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



