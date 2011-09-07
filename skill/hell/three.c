#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
	object weapon = me->query_temp("weapon");

	if(!target) target = offensive_target(me);

	if( !target
		||      !target->is_character()
		||      target->is_corpse()
		||      target==me)
		return notify_fail("你要对谁施展这一招「神·人·鬼」？\n");

	if(!me->is_fighting())
		return notify_fail("「神·人·鬼」只能在战斗中使用！\n");

	if(me->query("force") < 1000 )
		return notify_fail("你的内力不够！\n");

	me->add("force", -100);

	message_vision("\n$N双手划一大圆，猛然托天而举，伴着天上雷鸣电闪，祭出了「神·人·鬼」三招。\n", me);

	me->set("HellZhen", 7);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	me->set("HellZhen", 6);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 

	me->set("HellZhen", 5);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	me->delete("HellZhen");
	
	if( !target->is_fighting(me) ) {
		if( living(target) ) {
			if( userp(target) ) target->fight_ob(me);
			else target->kill_ob(me);
		}
	}

	me->start_busy(3);
	return 1;
}
