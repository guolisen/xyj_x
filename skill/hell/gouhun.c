// gouhun.c
#include <ansi.h>

inherit SSERVER;


//�ж��Ƿ���ҹ��
#define at_night() (NATURE_D->query_current_day_phase() / 6)


int cast(object me, object target)
{
	int k = at_night() ? 1 : -1;
	int success_adj = 120 + k * 60;
	int damage_adj = 120 + k * 60;
	int cost = 25 + 2 * me->query("mana_factor");
	int anti_magic = me->query_skill("gouhunshu") * 2 / (1 + me->query("betray/count"));

	if( !target ) target = offensive_target(me);

	if( !target
		|| !target->is_character()
		|| target->is_corpse()
		|| target == me)
		return notify_fail("��Ҫ���Լ��Ļꣿ\n");

	if((int)me->query("mana") < cost ) return notify_fail("��ķ��������ˣ�\n");

	me->add("mana", -cost);

	target->add_temp("apply/anti_magic", -anti_magic);

	SPELL_D->attacking_cast(
		me, 
		//attacker 
		target, 
		//target
		success_adj, 	
		//success adjustment
		damage_adj, 	
		//damage adjustment
		"sen", 		
		//damage type: could be "qi"/"kee", "shen"/"sen", ...default "both"
		HIC "$N��$n������Ц�ţ������������������������㵽���������\n" NOR,
		//initial message
		HIC "$n�ܵ�$NӰ�죬��Ȼ�е�겻�����ˣ�\n" NOR, 
		//success message
		HIC "����$n����רע����$N������\n" NOR, 
		//fail message
		HIC "����$n��һ�ɣ����컯��֮�£����ɶ����У�\n" NOR, 
		//backfire initial message
		HIC "���$n�����е�겻�����ˣ�\n" NOR
		//backfire hit message. note here $N and $n!!!
	);

	target->add_temp("apply/anti_magic", anti_magic);

	//me->start_busy(1 + random(2));
	return 5;	//3+random(5);
}
