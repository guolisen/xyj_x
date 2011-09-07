// by firefox 11/21/2009

inherit ITEM;
#include <ansi.h>
#include <xyj_x.h>

#define NAME			HIY"忘忧草"NOR
#define ID				"wangyou cao"
#define FLAG			"gift/wyc"

mapping remains = ([
	//"dismantle"	: 1,	"alchemy"	: 1,
]);

void create()
{
	set_name(NAME, ({ ID }));
	set_weight(90);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "棵");
		set("long", "一棵开着黄花的小草，吃下后会忘记师承和武功，潜能保留。\n");
		set("value", 100);
		set("drug_type", "补品");
	}
	set("is_monitored", 1);
	setup();
}

void init()
{
	add_action("do_eat", "eat");
}

int do_eat(string arg)
{
	object who = this_player();
	mapping skills = who->query_skills();
			
	if(arg != ID) return 0;
	if(who->query(FLAG)) return notify_fail("忘忧草只能吃一次。\n");
	who->add(FLAG, 1);
	
	//delete all skills
	SKI->clear_all(who);

	who->set("learned_points", who->query("potential") / 10);

	//delete menpai flag
	who->delete("spell_qiankun_on");
	who->delete("yuan-learn");

	//bonze
	if(who->query("bonze/class") == "bonze")
		who->set("name", who->query("bonze/old_name"));
	who->delete("bonze");

	//delete menpai
	who->delete("betray");
	who->delete("family");
	who->delete("class");
	who->set("title", "失忆者");

	message_vision(HIG"$N吞下一刻"NAME HIG"，所有的记忆都渐渐模糊，最终一片空白。\n"NOR, who);
	who->command("fool");
	
	destruct(this_object());
	return 1;
}
