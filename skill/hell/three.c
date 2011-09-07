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
		return notify_fail("��Ҫ��˭ʩչ��һ�С����ˡ�����\n");

	if(!me->is_fighting())
		return notify_fail("�����ˡ���ֻ����ս����ʹ�ã�\n");

	if(me->query("force") < 1000 )
		return notify_fail("�������������\n");

	me->add("force", -100);

	message_vision("\n$N˫�ֻ�һ��Բ����Ȼ������٣������������������������ˡ����ˡ������С�\n", me);

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
