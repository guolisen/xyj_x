
inherit ITEM;

#include <xyj_x.h>
#include <ansi.h>

#define PROP		"gift/holiday"

#define DATE		20120501
#define POT			30000


//#define ID			"mang guo"

//#define LONG		"愿MUD西游记一年更比一年红火。"
//#define LONG		"四时花竞巧，九子粽争新。祝大家端午愉快。"
//#define LONG		"唐初最盛胡饼，即后世月饼。祝大家中秋/国庆快乐。"

#define NAME		""
#define ID			""
//#define LONG		"愿大家节日快乐，原MUD西游记一年更比一年红火。"
//string* _tab = ({ ({"年糕", "nian gao"}), ({"饺子", "jiao zi"}), ({"汤圆", "tang yuan"}) });
#define LONG		"太忙了，祝大家吃得开心，玩得愉快。"
string* _tab = ({ ({"芒果", "mang guo"}), });


void create()
{
	string arr = random1(_tab);
	set_name(arr[0] + NAME, ({arr[1] + ID, "food"}));
	set_weight(0);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("no_drop", 1);
		set("unit", "个");
		set("long", LONG + "\n");
	}
	setup();
}


void init()
{
	add_action("do_eat", ({ "eat", "chi" }) );
}

//吃过了
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
		message_vision("$N拿起$n细细品味，感觉回味无穷。\n", who, me);
		who->add("potential", POT);
	} else {
		message_vision("$N一口吞下$n，如同猪八戒吃人参果，没尝出滋味。\n", who, me);
	}

	who->set("food", who->max_food_capacity());
	who->set("water", who->max_water_capacity());
	
	destruct(me);
	return 1;
}



