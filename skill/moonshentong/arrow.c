// arrow.c
#include <ansi.h>

inherit SSERVER;

int cast(object me, object target)
{
	int success_adj = 130;//��ǿ
	int damage_adj = 130;
	int cost = 25 + 2 * me->query("mana_factor");

	if( !target ) target = offensive_target(me);

	if( !target
		||      !target->is_character()
		||      target->is_corpse()
		||      target==me)
		return notify_fail("��Ҫ��˭ʩչ���������\n");

	if((int)me->query("mana") < cost )
		return notify_fail("��ķ���������\n");

	me->add("mana", -cost);

	SPELL_D->attacking_cast(
		me, 
		//attacker 
		target, 
		//target
		success_adj, 	
		//success adjustment
		damage_adj, 	
		//damage adjustment
		"both", 		
		//damage type: could be "qi"/"kee", "shen"/"sen", ...default "both"
		HIC "$N�������˼������ģ�����һ���������ڴˣ���������ֳ�һλ������Ƥ�Ĵ󺺡�\nֻ�����Ź��������ಡ���һ����һֻ�������ĳ�����$n������£�\n" NOR,
		//initial message
		HIC "���������$n����͸���������ʱѪ���ɽ���\n" NOR, 
		//success message
		HIC "ֻ��$n����һ�����������ò���$n�űߣ�أ�Բ������ݣ�\n" NOR, 
		//fail message
		HIC "����$n�Է���һ����������ಡ���һ������$N��\n" NOR,
		//backfire initial message
		HIC "���������$n����͸���������ʱѪ���ɽ���\n" NOR
		//backfire hit message. note here $N and $n!!!
		);

	me->start_busy(2);
	return 3 + 2;
}

