// mihun.c �Ի���
#include <ansi.h>

inherit SSERVER;

#define DURATION			30

void free(object target);

int cast(object me, object target)
{
	string msg;
	int success, ap, dp;

	if( !target ) target = offensive_target(me);

	if(me->query_skill("moonshentong",1) < 60)
		return notify_fail("�㻹ûѧ���Ի���������\n");

	if( !target
		||      !target->is_character()
		||      target->is_corpse()
		||      target==me)
		return notify_fail("������˭�Ļꣿ\n");  

	if(target->query_temp("no_move"))
		return notify_fail(target->name() + "�Ѿ��겻���ᣬ����ľ���ˣ�\n");  

	if((int)me->query("mana") < 200 )
		return notify_fail("��ķ���������\n");

	me->add("mana", -200);


	msg = HIC"$N��ͷ�������˾����ģ���̧��ͷ����$n���ĵ�һЦ��\n"NOR;

	success = 1;

	ap = me->query_skill("spells") / 10;
	ap = ap * ap * ap / 12 ;

	ap += me->query("daoxing") / 1000;
	dp = target->query("daoxing") / 1000;

	ap += me->query_per() * 5000 / 1000;
	dp += target->query_per() * 5000 / 1000;

	ap += me->query("mana") * 200 / 1000;
	dp += target->query("mana") * 200 / 1000;
	
	if(random(ap+dp) < dp) success = 0;

	//here we compare current mana. this is important. you need recover to try again.

	if(success == 1 ){
		msg +=  HIR "$n������ؿ���$N������ϧ��֮����Ȼ���𣬾�Ȼ�����Լ���ս��֮�С�\n" NOR;
		target->set_temp("no_move", 1);

		call_out("free", DURATION, target);
	}	    
	else {
		msg +=  HIR "$n���ĵؿ���$Nһ�ۣ�����Ϊ������\n" NOR;	
		me->start_busy(1);
		if( living(target) ) target->kill_ob(me);
	} 

	message_vision(msg, me, target);

	return 3 + 2;
}

void free(object target)
{
	if (target)
		target->delete_temp("no_move");      
	return;
}

