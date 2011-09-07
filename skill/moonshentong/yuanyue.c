// lifeheal.c

#include <ansi.h>

#define POISON			"moon_poison"

int exert(object me, object target)
{
	int skill = me->query_skill("moonforce", 1);

	if ( !target || target->is_corpse()) 
		return notify_fail("你想替谁解除蚀月咒？\n");
	if (!target->query_condition(POISON))
		return notify_fail("没中蚀月咒瞎搅和什么！\n");
	if( me->is_fighting() || target->is_fighting())
		return notify_fail("战斗中无法运功疗伤！\n");

	if( me->query("force") - me->query("max_force") <  600 )
		return notify_fail("你的真气不够。\n");

	if ( me->query_skill("force") < 100 || skill < 80)
		return notify_fail("你的内功修为不足以替人解除蚀月咒。\n");

	message_vision(HIY"$N坐了下来默默的念起经来，声音越来越柔和，全身隐隐发出圣洁的光辉。\n\n"NOR,	me);

	if (random(skill - 60) > 10) {
		target->apply_condition(POISON, 0);
		message_vision(HIY"$N心中渐渐感到平和安静，轻轻的舒了一口气慢慢睁开眼睛。\n"NOR, target);
	} else {
		message_vision(HIY"$N突然脸色苍白，似乎体力不支，竟呕出一口血来……\n"NOR, me);
	}

	target->receive_cuiring("kee", 10 + me->query_skill("force") / 3);
	me->add("force", -150);
	
	return 1;
}
