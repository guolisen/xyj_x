// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"love"
#define NAME			HIM"催情大法"NOR
#define CD				20
#define DURATION		4

void tired(object who, int str);

int cast(object me, object target)
{
	int skill = me->query_skill("spells");
	mapping req = ([
		"cd"		: ([ ID			: 1 ]),
		"skill1"	: ([ "spells"	: 50 ]),
		"prop"		: ([ "mana"		: skill/2 ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ "per" : 3, "cps" : 3, "str" : -3, DEXP : 1, "max_mana" : 3 ]),
		"skill"		: ([ "spells" : 3]),
		"temp"		: ([ "no_cast" : -1]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("勾引谁？\n");
	if(me->query_per() < 20) return notify_ok("你太丑了，别去吓人了。\n");
	if(BUFF->find(target, ID)) return notify_ok("对方已经被迷倒了！\n");
	if(!BTL->require(me, NAME, req)) return 1;

	BTL->pay(me, req["prop"]);
	
	BUFF->start_cd(me, ID, NAME, CD);

	msv(HIM"\n$N深情的望着$n，满眼秋波目光迷离，轻吟催情大法...\n"NOR, me, target);

	if(BTL->cmp_random20(me, target, cmp_parm) > 80) {
		int force = target->query("force");
		target->add("force", max2(-force, -skill * 4));
		
		msv(HIM"$n眼光一荡呆在那里，如痴如醉的望着$N...\n\n"NOR, me, target);
		target->command("grin");

		tired(target, skill / 2);
		tired(me, 0);
		call_out("love2_done", DURATION * SEC_PER_HB, me, target);

		SKILL_D("pansi-dafa")->random_level_up(me);
	} else {
		msv(HIM"$n仿佛不解风情，对$N视若无睹。\n\n"NOR, me, target);
	}
	return DURATION;
}

void tired(object who, int str)
{
	mapping buff = ([
		"id"		: ID,
		"name"		: NAME,
		"comment"	: "有气无力。",
		"duration"	: DURATION * 3,
		"add_apply" : ([ "strength" : -str ]),
	]);
	int sen = who->query("max_sen") / 3;
	who->receive_curing("sen", sen);	//精神愉悦
	who->receive_heal("sen", sen);
	if(who->query_busy() < DURATION) who->start_busy(DURATION);
	BUFF->add(who, buff);
}

void love2_done(object me, object who)
{
	object env = environment(who);
	if(same_env(me, who) && !env->query("no_fight")) {
		msv(CYN"$N打了一个寒颤。\n"NOR, who);
		BTL->fight_enemy(who, me);
	}
}

