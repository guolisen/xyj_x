// 蚀月咒?
inherit SSERVER;
#include <ansi.h>

#define POISON			"moon_poison"

int cast(object me, object target)
{
	string msg;
	int success, ap, dp;
	int skill = me->query_skill("spells");

	if(skill < 80) return notify_fail("你还没学会蚀月咒。。。\n");
	
	if( !target ) target = offensive_target(me);
	if( !target
		||      !target->is_character()
		||      target->is_corpse()
		||      target==me)
		return notify_fail("你想对谁施展蚀月咒？\n");  

	if(target->query_condition(POISON))
		return notify_fail(target->name() + "已经中邪了！\n");  

	if(me->query("mana") < skill) return notify_fail("你的法力不够！\n");

	me->add("mana", -skill);

	msg = HIC"$N低头默默念起咒文，手中渐渐聚起一团光球，雪白的脸庞似乎发射出柔和的光芒。\n"NOR;

	success = 1;
	ap = me->query_skill("spells") / 10;
	ap = ap * ap * ap /10 ;
	ap += me->query("daoxing") / 2 / 1000;

	dp = target->query("daoxing") / 2 / 1000;

	ap += me->query_spi() * 2500 / 1000;
	dp += target->query_spi() * 2500 / 1000;

	ap += me->query("mana") * 200 / 1000;
	dp += target->query("mana") * 200 / 1000;

	if(random(ap) < dp / 2) success = 0;
		
	if(success == 1) {

		msg +=  HIR "$n见到$N祥宁之态，娇美不可方物，心中一荡，却不防那光球一闪，突然射向$n。\n" NOR;
		target->apply_condition(POISON, skill / 10);

		target->	receive_wound("sen", skill, me);
		target->receive_wound("kee", skill);
		target->receive_damage("sen", skill);
		target->receive_damage("kee", skill);
		
		if( living(target) ) target->kill_ob(me);

		me->start_busy(1);
	} else {
		msg +=  HIR "$N脸色苍白，似乎体力不支，光球在手中渐渐褪去。！\n" NOR;
		me->apply_condition(POISON, skill / 20);
	}

	message_vision(msg, me, target);
	return 1;
}

