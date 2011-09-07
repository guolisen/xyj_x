
//�����ֻ�

#include <ansi.h>

inherit F_DBASE;
inherit SSERVER;

void delay_effect(object me, object target, object weapon,int power);

int perform(object me, object target)
{
	int delay,skill;
	object weapon=me->query_temp("weapon");
	
	if( !target ) target = offensive_target(me);
	if (!target) return notify_fail("��˭��\n");
	if (!me->is_fighting(target))
		return notify_fail("���ǲ��ڴ�ܡ�\n");
	skill=me->query_skill("tonsillit",1);        
	if (skill<60) return notify_fail("����������������졣\n");
	skill=me->query_skill("whip");
	if (skill<100) 
		return notify_fail("��ı޷�̫��ˡ�\n"); 
	if( (int)me->query("force") < 300 )      
		return notify_fail("�������������\n");
	if( (int)me->query_temp("lunhui_delay") )
		return notify_fail("���Ѿ���ʩչ�����ֻ��ˡ�\n");

	me->add("force", -200);
	delay=4;//random(4)+1;
	message_vision(HIB"$N��������һЦ������"+weapon->name()+
		HIB"ͻȻ����������$nһ����ϲ��ץס���ᣬ��ǰ����һ�ּ�����\n"NOR, me,target);
	//        tell_object(me,delay+"\n");
	me->set_temp("lunhui_delay", 1);
	me->start_busy(delay);
	
	call_out("delay_effect", delay * 2, me, target, weapon, delay);

	return 1;
}


mapping _action = ([
	"action"		: "$N���һ��������$w�����������ڰ�գ����С���ճ����������š�\n$nֻ����ȫ�����$w����֮��",
	"damage"		: 50,
	"force"			: 50,
	"dodge"			: -20,
	"parry"			: -20,
	"damage_type"	: "����",
]);

void delay_effect(object me, object target, object weapon, int power)
{
	int attack,damage;
	object env;

	if(!me) return;
	me->delete_temp("lunhui_delay");
	env = environment(me);
	
	if(!target || env != environment(target) || env->query("no_fight")) return;		// 2010.11 for ��̨�´�����
	if(!weapon || me->query_temp("weapon") != weapon) return;	

	message_vision(HIR"$N����ͻȻһ�䣬����"+weapon->name()
		+ HIR"���������Ӱ����$n����·ȫ��������\n"NOR,me,target);
	message_vision(HIR"$N���������������������ܶ������ܹ�������ֻ�֮�࣬������͸��������\n"NOR,target);
	
	attack = me->query_skill("hellfire-whip") * power;
	damage = power * me->query_temp("apply/damage") + me->query("force_factor");

	target->add_temp("apply/defense", -attack);								// 2010.11 for ��ֹ���
	me->add_temp("apply/damage", damage);
	
	me->set("actions", _action);
	COMBAT_D->do_attack(me, target, weapon);
	me->reset_action();

	me->add_temp("apply/damage", -damage);									// 2010.11 for damage bug
	target->add_temp("apply/defense", attack);	
}

