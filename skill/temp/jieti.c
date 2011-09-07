
// jieti.c ��ħ����󷨡�

#include <ansi.h>

inherit SSERVER;


void kill_sb(object killer, object victim)
{
	victim->kill_ob(killer);
	victim->receive_damage("sen", victim->query("max_sen") + 1, killer);
	victim->receive_wound("sen", victim->query("max_sen") + 1, killer);
	victim->receive_damage("kee", victim->query("max_kee") + 1, killer);
	victim->receive_wound("kee", victim->query("max_kee") + 1, killer);
	COMBAT_D->report_status(victim);
}

int cast(object me, object target)
{
	string msg;
	int success, ap, dp;

	if( (string)me->query("class") != "yaomo" )
		return notify_fail("ֻ����ħ����ʩչ��ħ����󷨡�\n");

	if( !target ) target = offensive_target(me);

	if( !target
		|| !target->is_character()
		|| target->is_corpse()
		|| target==me)
		return notify_fail("��Ҫ��˭ʩչ��ħ����󷨣�\n");

	if(me->query("mana") < 110 || me->query("max_mana") < 110 )
		return notify_fail("��ķ���������������Чʩչ��ħ����󷨣�\n");

	if(me->query("force") < 60 || me->query("max_force") < 60 )
		return notify_fail("�������������������Чʩչ��ħ����󷨣�\n");

	if(me->query("sen") < 100 || me->query("sen") < me->query("max_sen")/2 )
		return notify_fail("���޷����о���ʩչ��ħ����󷨣�\n");

	if( me->query("daoxing") < target->query("daoxing")/10  )
		return notify_fail("�Է�����ǿ̫���ˣ����Ǳ������ɣ�\n");

	msg = HIC
		"$N�������˼������ģ�˫����ס�Դ������췢��һ����˻��\n\n��Ȼ��$N���Լ���ͷ����һҧ��һ��Ѫ����$n���˹�ȥ��\n" NOR;

	success = 1;
	ap = me->query_skill("spells") / 10;
	ap = ap * ap * ap /10 ;
	ap += me->query("daoxing") / 1000;
	ap = 4*ap; //this is for ƴ�� so easier.
	dp = target->query("daoxing") / 1000;
	if( random(ap + dp) < dp ) success = 0;
	//here we compared exp and spells level. 
	//note: has nothing to do with target's spells level.

	ap = me->query("max_mana");
	dp = target->query("max_mana");
	if( ap < random(dp) ) success = 0;
	//here we compared max_mana.
	//if the attacher has half of the max_mana of the target, 
	//he has 50% chance to kill his target, which is reasonable.

	me->add_maximum_mana(-100);
	me->add_maximum_force(-50);
	me->save();

	if(success == 1 ){//now both die.
		msg +=  HIR "���$n��Ѫ����ס����ʱ����һ���ҽУ�\n��$NҲ����һ̱�����ڵ��ϡ�\n" NOR;
		message_vision(msg, me, target);

		kill_sb(me, target);
		kill_sb(target, me);
		
		me->heart_beat();
		target->heart_beat();		
	} else {
		msg +=  HIR "���Ѫ��$n����������������ס��$N��\n$N��̾һ��������һ̱�����ڵ��ϡ�\n" NOR;
		message_vision(msg, me, target);

		kill_sb(target, me);
		me->heart_beat();
	} 

	return 3 + 2;
}

