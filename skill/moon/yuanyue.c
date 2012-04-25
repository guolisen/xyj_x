// firefox 2012.4

#include <ansi.h>

#define POISON			"moon_poison"

int exert(object me, object target)
{
	int skill = me->query_skill("moonforce", 1);
	int duration, cost;

	if(!target || target->is_corpse()) 
		return notify_fail("你想替谁解除蚀月咒？\n");

	duration = target->query_condition(POISON)
	if (duration > 0) return notify_fail("目标没中蚀月咒。\n");

	if(me->is_fighting() || target->is_fighting())
		return notify_fail("战斗中无法运功疗伤！\n");

	cost = duration * 100;
	if(me->query("force") < cost) return notify_fail("你的真气不足。\n");

	message_vision(HIY"$N坐了下来默默的念起经来，声音越来越柔和，全身隐隐发出圣洁的光辉。\n\n"NOR,	me);

	me->add("force", -cost);
	if(random(skill) > duration) {
		message_vision(HIY"$N心中渐渐感到平和安静，轻轻的舒了一口气慢慢睁开眼睛。\n"NOR, target);

		target->apply_condition(POISON, 0);
		target->receive_cuiring("kee", 10);
	} else {
		message_vision(HIY"$N突然脸色苍白，似乎体力不支，竟呕出一口血来……\n"NOR, me, target);
	}
	
	return 1;
}
