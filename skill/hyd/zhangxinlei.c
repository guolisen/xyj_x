#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
	int cost = 100 + me->query("force_factor");

	if( !target ) target = offensive_target(me);

	if( !target
		||      !target->is_character()
		||      target->is_corpse()
		||      target==me)
		return notify_fail("你要对谁施展这一招掌心雷？\n");

	if(!me->is_fighting())
		return notify_fail("掌心雷只能在战斗中使用！\n");

	if(me->query("force") < cost * 2)
		return notify_fail("你的内力不够！\n");

	if(me->query_skill("moyun-shou", 1) < 50)
		return notify_fail("你的摩云手级别还不够，使用这一招会有困难！\n");

	message_vision("\n$N大喝一声“掌心雷”！\n", me);

	me->set_temp("moyunshou_per", 6);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	me->delete_temp("moyunshou_per");

	if( !target->is_fighting(me) ) {
		if( living(target) ) {
			if( userp(target) ) target->fight_ob(me);
			else target->kill_ob(me);
		}
	}

	me->start_busy(2 + 1);
	return 1;
}
