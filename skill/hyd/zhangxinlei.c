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
		return notify_fail("��Ҫ��˭ʩչ��һ�������ף�\n");

	if(!me->is_fighting())
		return notify_fail("������ֻ����ս����ʹ�ã�\n");

	if(me->query("force") < cost * 2)
		return notify_fail("�������������\n");

	if(me->query_skill("moyun-shou", 1) < 50)
		return notify_fail("���Ħ���ּ��𻹲�����ʹ����һ�л������ѣ�\n");

	message_vision("\n$N���һ���������ס���\n", me);

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
