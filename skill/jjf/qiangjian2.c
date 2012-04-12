//Last modified by pkyou@2010-3-11

#include <ansi.h>
#include <combat.h>

inherit SSERVER;

#define min2(a, b) ((a) < (b) ? (a) : (b))

int perform(object me, object target)
{
	int spear = me->query_skill("bawang-qiang", 1);
	int mace = me->query_skill("wusi-mace", 1);
	int anti_defense = spear * 2;
	int anti_armor;

	object weapon1 = me->query_temp("weapon");
	object weapon2 = present("mace", me);

	if(!target) target = offensive_target(me);
	if(!target || !me->is_fighting(target) || !living(target))
		return notify_fail("��ǹ���ﵡ�ֻ����ս����ʹ�ã�\n");

	if((int)me->query("max_force") < 500)
		return notify_fail("�������������\n");

	if((int)me->query("force") < 500 )
		return notify_fail("����������㣡\n");

	if(spear < 100)	return notify_fail("��İ���ǹ���𻹲�����ʹ����һ�л�������!\n");

	if(mace < 100) return notify_fail("�����˽ﵼ��𻹲�����ʹ����һ�л�������!\n");

	if(me->query_skill_mapped("mace") != "wusi-mace")
		return notify_fail("��ǹ���ﵡ����������˽ﵷ�!\n");

	if(!objectp(weapon2) || weapon2->query("skill_type") != "mace")		//�޸������ֵ�bug
		return notify_fail("û���ôǹ����?\n");

	me->add("force", -200);

	message_vision(HIC"\n$N���㾫�񣬶��ִ̳�һǹ!\n"NOR, me, target);

	COMBAT_D->do_attack(me, target, weapon1, TYPE_QUICK);

	message_vision(HIC"\n����$n��æ���мܣ�$N���" + weapon2->query("name") + "�������¡�\n"NOR, me, target);

	weapon1->unequip();
	weapon2->wield();
	
	anti_armor = min2(target->add_temp("apply/armor"), mace / 2);

	target->add_temp("apply/armor", -anti_armor);		//�������ж۱���������Ϊ�˶Ը��ؼ�
	
	COMBAT_D->do_attack(me, target, weapon2, TYPE_QUICK);
	
	target->add_temp("apply/defense", -anti_defense);	//ǹ�����ң�����ﵷ�����	
	
	COMBAT_D->do_attack(me, target, weapon2, TYPE_QUICK);

	target->add_temp("apply/defense", anti_defense);
	target->add_temp("apply/armor", anti_armor);

	if( !target->is_fighting(me) ) {
		if( living(target) ) {
			if( userp(target) ) target->fight_ob(me);
			else target->kill_ob(me);
		}
	}

	weapon2->unequip();
	weapon1->wield();

	me->start_busy(2);

	return 1;
}

