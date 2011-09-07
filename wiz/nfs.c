// by firefox 11/21/2009

inherit NPC;
inherit "/d/sldh2/feature/stat";
inherit "/d/sldh2/feature/buff";
inherit "/d/sldh2/feature/util";

/*

平衡门派
门派统计，哪个门派少就多buff哪个门派。


1/10

max_kee，不行，怪等比增加
dodge，attack，防止数值太高溢出
damage 不行


门派负反馈系统

force	增加打坐效率，提高技能伤害
armor	减伤，系数需要实测
defance

法术负反馈系统

spells	有效降低怪法术命中，提升自身命中

法术，兵器引入负反馈，玉帝是如何平衡自然界的？战斗中，取兵器类型。*/


#include <ansi.h>

#define SPELL_POT		20
#define DEFENSE_POT		20
#define BUFF_ID			"nfs"
#define STAT_ID			"sys_stat"
#define MAX_LVL			400

#define MM				"mm_anadem"
#define MM_LVL			200

int mm_anadem(object user)
{
	if(user->query(MM) && !query_buff(user, MM)) {
		add_buff(user,  ([
			"id"		: MM,
			"name"		: HIM"美眉花环"NOR,
			"comment"	: "对MM的优待，提高法术防御护甲。",
			"add_apply"	: ([
				"spells"	: MM_LVL,
				"defense"	: MM_LVL,
				"armor"		: MM_LVL * 2,
				"personality"	: 20,
			]),
		]));
	}
}

int on_nfs(mapping buff)
{
	object me = buff["me"];
	me->do_stat();
	foreach(object user in users()) {
		string spells = user->query_skill_mapped("spells");
		string family = user->query("family/family_name");
		int spells_lvl = 1;
		int defense_lvl = 1;
		if(spells) {
			int pct = me->str_pct("spells", spells) + 1;
			spells_lvl = 100 * SPELL_POT / pct;
		}
		if(family) {
			int pct = me->str_pct("family", family) + 1;
			defense_lvl = 100 * DEFENSE_POT / pct;
		}
		remove_buff2(user, BUFF_ID);
		add_buff(user,  ([
			"id"		: BUFF_ID,
			"name"		: HIG"师门的护佑"NOR,
			"comment"	: "提高法术和防御。",
			"add_apply"	: ([
				"spells"	: min2(spells_lvl, MAX_LVL),
				"defense"	: min2(defense_lvl, MAX_LVL),
			]),
		]));
		if(getuid(user) == "firefox")
			trace(BUFF_ID" 你得到了spells:" + spells_lvl + " defense:" + defense_lvl, user);
		//mm_anadem(user);	//顺便为mm增加了花环
	}
	return 1;
}

//对象析构，清理所有buff
int remove()
{
	foreach(object user in users()) {
		remove_buff2(user, BUFF_ID);
	}
	::remove();
	return 0;
}

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
	::init();
	add_action("do_top", "top");
	add_action("do_skill", "skill");

	if(!query_buff(this_object(), STAT_ID)) {
		add_buff(this_object(),  ([
			"id"		: STAT_ID,
			"name"		: HIG"实力统计"NOR,
			"comment"	: "定时统计门派/法术的实力。",
			"interval"	: 60,
			"timer_act"	: (: on_nfs :),
		]));
	}
}

int do_skill(string arg)
{
	if(!arg) return 1;
	foreach(object user in users()) {
		int skill = user->query_skill(arg, 1);
		if(skill) printf("%s: %d\n", getuid(user), skill);
	}
	return 1;
}