// by firefox 11/21/2009

inherit ITEM;
inherit "/d/sldh2/feature/util";

#include <ansi.h>

string SKILL_PROP = "book/skill";

void create()
{
	set_name("石片", ({ "shi pian" }));
	
	if(!query(SKILL_PROP)) set(SKILL_PROP, "yaofa");

	set("long", "一块石片，刻着密密麻麻的字迹，隐约可见第一行是：『"
		+ to_chinese(query(SKILL_PROP)) + "』。");
	set("unit", "块");
	set("value", 10000);
	
	setup();
}


void init()
{
	add_action("do_study", "study");
	add_action("do_study", "read");
}

int do_study(string arg)
{
	object me = this_object();
	object who = this_player();

	if(arg && present(arg, who) == me) {
		string skill = query(SKILL_PROP);
		if(who->query_skill(skill, 1)) return fail_msg("上面的内容对你来说太浅了。\n");
		who->set_skill(skill, 3);
		write(HIC"你认真的研究着石片上的文字，突然豁然开朗，对『" + to_chinese(skill) + "』有所领悟！\n"NOR);
		who->command("jump");
		message_vision("$N一失手，$n掉在地上摔得粉碎。\n", who, me);
		destruct(me);
		return 1;
	}
	return 0;
}
