// ʴ����?
inherit SSERVER;
#include <ansi.h>

#define POISON			"moon_poison"

int cast(object me, object target)
{
	string msg;
	int success, ap, dp;
	int skill = me->query_skill("spells");

	if(skill < 80) return notify_fail("�㻹ûѧ��ʴ���䡣����\n");
	
	if( !target ) target = offensive_target(me);
	if( !target
		||      !target->is_character()
		||      target->is_corpse()
		||      target==me)
		return notify_fail("�����˭ʩչʴ���䣿\n");  

	if(target->query_condition(POISON))
		return notify_fail(target->name() + "�Ѿ���а�ˣ�\n");  

	if(me->query("mana") < skill) return notify_fail("��ķ���������\n");

	me->add("mana", -skill);

	msg = HIC"$N��ͷĬĬ�������ģ����н�������һ�Ź���ѩ�׵������ƺ��������͵Ĺ�â��\n"NOR;

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

		msg +=  HIR "$n����$N����̬֮���������ɷ������һ����ȴ�����ǹ���һ����ͻȻ����$n��\n" NOR;
		target->apply_condition(POISON, skill / 10);

		target->	receive_wound("sen", skill, me);
		target->receive_wound("kee", skill);
		target->receive_damage("sen", skill);
		target->receive_damage("kee", skill);
		
		if( living(target) ) target->kill_ob(me);

		me->start_busy(1);
	} else {
		msg +=  HIR "$N��ɫ�԰ף��ƺ�������֧�����������н�����ȥ����\n" NOR;
		me->apply_condition(POISON, skill / 20);
	}

	message_vision(msg, me, target);
	return 1;
}

