// by firefox 11/21/2009

inherit NPC;
inherit "/d/sldh2/feature/stat";
inherit "/d/sldh2/feature/buff";
inherit "/d/sldh2/feature/util";

#include <ansi.h>

#define SPELL_POT		20
#define DEFENSE_POT		20
#define BUFF_ID			"nfs"
#define STAT_ID			"sys_stat"
#define MAX_LVL			400

#define MM				"mm_anadem"
#define MM_LVL			200


//对象析构，清理所有buff


void create()
{
	set_name("伊娃", ({ "eve", "robot" }));
	set("long", "\n一个统计机器人，发出top指令，她会告诉你统计信息。\n\n");
	set("title", HIY"统计机器人"NOR);
	set("gender", "女性");
	set("age", 18);
	set("per", 120);

	setup();
}

void init()
{
	add_action("do_reward", "reward");
}


int do_reward(string arg)
{

	foreach(object user in users()) {
		clear_buff(user);
	}
	return 1;

}

