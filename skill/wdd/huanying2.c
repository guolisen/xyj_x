// by firefox 11/21/2009

inherit SSERVER;
inherit "/d/sldh2/feature/util.c";
inherit "/d/sldh2/feature/buff";

#include <ansi.h>

#define BUFF_ID			"huanying2"
#define BUFF_NAME		"幻影"

int cast(object me, object target)
{
	int skill = me->query_skill("yaofa", 1);
	mapping req = ([
		"ex_temp"	: ([ "yinshen_busy"		: "隐身中无法施展幻影。"]),
		"ex_value"	: ([ "env/invisibility"	: "隐身中无法施展幻影。"]),
		"skill1"	: ([ "yaofa"		: 250]),
		"value"		: ([ "mana"			: 100]),
	]);
	mapping buff = ([
		"id"		: BUFF_ID,
		"name"		: BUFF_NAME,
		"comment"	: "隐于幻影状态。",
		"duration"	: 10,
		"temp"		: ([
			"no_heal_up/yinshen" : 1,
			"yinshen_busy"	: 1,
		]),
		"replace"	: ([ "env/invisibility"	: 1 ]),
		"stop_msg"	: "青烟散尽，隐隐出现了$N的身形。\n",
		"post_act"	: function(object target, mapping buff) {

		},
	]);
	if(query_cd(me, BUFF_ID)) return fail_msg("你还不能施放幻影。\n");
	if(!require(me, BUFF_NAME, req)) return 1;
	pay(me, req["value"]);
	printf("你口中默念咒文，喷出一股青烟。瞬间一个人影出现在众人面前，而你则隐秘无踪。\n");

	//隐身，用来逃命或疗伤
	if(!require(me, BUFF_NAME, req)) return 1;
	pay(me, req["value"]);
	add_buff(me, buff);
	buff_start_cd(me, buff, 15);

	//脱离仇恨
	me->remove_all_killer();
	foreach(object who in all_inventory(environment(me))) {
		if(living(who)) who->remove_killer(me);
	}

	//幻影来顶替
	{
		object obj = new("/d/sldh2/feature/hufa");
		obj->move(environment(me));
		obj->invocation(me);
		obj->set_temp("invoker", me);
	}
	return 1;

}
