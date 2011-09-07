//added by huadao .2010.07.24
#include <ansi.h>

inherit SSERVER;

#define CD			1

mapping* _acts = ({
	([
		"action"		: "$N��������Ծ�𣬷��ѩ�轣�籩���滨����$nӭ�����"NOR,
		"damage"		: 300,
		"damage_type"	: "����",
	]),
	([
		"action"		: "$N����бб����Ʈ����Ҳ����ͷ�����־ʹ̳���һ��",
		"damage"		: 300,
		"damage_type"	: "����",
	]),
	([
		"action"		: "$Nһ��ŭ߳����������ǧ��֧���������������ѩ����$n",
		"damage"		: 300,
		"damage_type"	: "����",
	])
});

int perform(object me, object target)
{
	object weapon = me->query_temp("weapon");
	int skill = me->query_skill("snowsword", 1);

	if(!target) target = offensive_target(me);

	if(!target
		||      !target->is_character()
		||      target->is_corpse()
		||      target == me)
		return notify_fail("��Ҫ��˭ʩչ�������ѩ����\n");

	if(me->query("force") < 400)
		return notify_fail("�������������\n");

	if(!me->is_fighting())
		return notify_fail("�������ѩ��ֻ����ս����ʹ�ã�\n");

	if( skill < 50)
		return notify_fail("��ķ��ѩ�轣�����𻹲�����ʹ����һ�л������ѣ�\n");

	if(me->query("betray/count"))
		return notify_fail("[�����ѩ]���¹�����֮�ܣ�\n");

	if( me->query("force_factor") > 0)
		return notify_fail("�������ѩ���������в������������������ܽ������飿\n");

	if(!cd_start(me, "feixue", CD)) 
		return notify_fail("�����ö�Ͳ����ˣ�\n");

	me->add("force", -200);
	
	message_vision(HIW"\n$N��߳һ�������弱�����������Ž����������������ѩ����$n��\n"NOR, me, target);

	if(userp(target)) skill *= -1;
	
	me->add_temp("apply/attack", skill);

	foreach(mapping act in _acts) {
		me->set("actions", act);
		COMBAT_D->do_attack(me, target, weapon);
	}
	me->reset_action();

	me->add_temp("apply/attack", -skill);

	if(!target->is_fighting(me) && living(target)) {
		if( userp(target) ) target->fight_ob(me);
		else target->kill_ob(me);
	}

	return 1;
}


