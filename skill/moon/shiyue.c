// 蚀月咒?
inherit SSERVER;
#include <ansi.h>
#include <xyj_x.h>

#define POISON			"moon_poison"
#define NAME			"蚀月咒"
#define MSG0			HIC"$N低头默默念起咒文，手中渐渐聚起一团光球，雪白的脸庞似乎发射出柔和的光芒。\n"NOR
#define MSG1			HIR"$n见到$N祥宁之态，娇美不可方物，心中一荡，却不防那光球一闪，突然射向$n。\n"NOR
#define MSG2			HIR"$N脸色苍白，似乎体力不支，光球在手中渐渐褪去。！\n"NOR

int cast(object me, object target)
{
	int skill = me->query_skill("spells");
	mapping req = ([
		"skill1"	: ([ "moonshentong"	: 60 ]),
		"prop"		: ([ "mana"			: skill ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ DEXP : 1, "mana_factor" : 1 ]),
		"skill"		: ([ "spells" : 2]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("你想对谁施展蚀月咒？");
	if(target->query_condition(POISON)) return notify_fail(target->name() + "已经中邪了！\n");  
	if(!BTL->require(me, NAME, req)) return 1;
	BTL->pay(me, req["prop"]);

	msv(MSG0, me, target);

	if(BTL->cmp_random20(me, target, cmp_parm) > 85) {
		msv(MSG1, me, target);

		target->apply_condition(POISON, skill / 8);
		target->receive_damage("sen", skill, me);
		target->receive_damage("kee", skill);
		target->receive_wound("sen", skill / 2);
		target->receive_wound("kee", skill / 2);

		me->start_busy(1);
	} else {
		msv(MSG2, me, target);
		me->apply_condition(POISON, skill / 20);
	}
	BTL->fight_enemy(target, me);
	return 2;
}

