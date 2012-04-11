// mihun.c 迷魂术
#include <ansi.h>

inherit SSERVER;

#define DURATION			30
#define NAME			"蚀月咒"
#define MSG0			HIC"$N低头轻声念了句咒文，又抬起头来朝$n妩媚地一笑！\n"NOR
#define MSG1			HIR"$n神不守舍地看着$N，怜香惜玉之心由然而起，竟然忘了自己在战斗之中。\n"NOR
#define MSG2			HIR"$n鄙夷地看了$N一眼，毫不为所动！\n"NOR

int cast(object me, object target)
{
	int skill = me->query_skill("spells");
	mapping req = ([
		"skill1"	: ([ "moonshentong"	: 40 ]),
		"prop"		: ([ "mana"			: skill ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ DEXP : 1, "mana_factor" : 1 ]),
		"skill"		: ([ "spells" : 2]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("你想迷谁的魂？");
	if(target->query_temp("no_move")) return notify_fail(target->name() + "已经魂不守舍，呆若木鸡了！\n");  
	if(!BTL->require(me, NAME, req)) return 1;
	BTL->pay(me, req["prop"]);

	msv(MSG0, me, target);

	if(BTL->cmp_random20(me, target, cmp_parm) > 85) {
		msv(MSG1, me, target);


	} else {
		msv(MSG2, me, target);
		me->apply_condition(POISON, skill / 20);
		me->start_busy(1);
	}
	BTL->fight_enemy(target, me);
	return 3 + 2;
}

