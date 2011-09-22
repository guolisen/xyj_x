
inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>
#include <combat.h>

#define CD				15
#define BUFF_ID			"bleeding"
#define BUFF_NAME		"��Ѫ"

#define YS_ID			"yinshen2"

int on_timer(mapping buff);

int perform(object me, object target)
{
	object weapon = me->query_temp("weapon");
	int cost = 200;
	int ap, dp;
	string msg;

	if(!target) target = offensive_target(me);

	if(!target || !target->is_character() || target->is_corpse() || target == me)
		return notify_fail("��Ҫ����˭��\n");
	
	if(!target->is_fighting(me))
		return notify_fail("����û���ڴ�ܣ�\n");
	
	if(me->query("force") < cost)
		return notify_fail("���������̣����Գ��С�\n");

	
	if(!cd_start(me, "im_pfm", CD))
		return notify_fail("�����õ�̫��̫�ľͲ����ˡ�\n");

	me->add("force", -cost);

	message_vision(HIB"ͻȻ������ӵ��𣬲�Ӱ��΢�⣻$N��������ҫ��â��ֱ��$n��\n"NOR, me, target);
	msg = CYN"$N��æ�����мܣ�����¥ץ��䣬�����ԧ�졣����ֹ����";

	ap = COMBAT_D->skill_power(me, "sword", SKILL_USAGE_ATTACK);
	dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE);
	dp += COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE);

	dp /= 2;

	if(target->query_temp("no_move")) dp /= 2;
	if(target->is_busy()) dp /= 3;
	
	trace("ap:" + ap + " dp:" + dp);
	
	if(ap > dp + random(dp * 2)) {	//��������25%��һ�����������0%
		
		int heal = me->query_skill_mapped("spells") == "yaofa";
		int power = 1 + me->query_skill("huntian-qigong", 1) / 20;
		int damage = power * me->query_temp("apply/damage");
		mapping buff = BUFF->find(target, BUFF_ID);

		trace("total damage:" + damage);

		if(buff) {
			buff["_damage"] += damage;
		} else {
			buff = ([
				"id"		: BUFF_ID,
				"name"		: BUFF_NAME,
				"comment"	: "����Ѫ����ֹ��",
				"interval"	: 2,
				"timer_act"	: (: on_timer :),
				"_damage"	: damage,
				"_heal"		: heal,
				"_attacker"	: me,
			]);
			BUFF->add(target, buff);
		}
		message_vision(msg + "Ѫ����ע��\n"NOR, target);
	} else {
		message_vision(msg + "��������\n"NOR, target);
	}

	return 1;
}

//Ŀ�괦�ڰ�ȫ��
int in_safy(object who)
{
	object env = environment(who);
	return env && (env->query("no_fight") || env->query("no_magic"));
}

int on_timer(mapping buff)
{
	object me = buff["me"];
	int damage = buff["_damage"] / 3;
	object attacker = buff["_attacker"];
	mapping ys_buff = BUFF->find(me, YS_ID);

	if(in_safy(me) || damage < 10) return 0;

	me->add("force", -damage*5);		//����Ҳ������Ѫ����
	
	me->receive_damage("kee", damage);
	me->receive_wound("kee", damage, attacker);
	
	if(buff["_heal"] && attacker && attacker->is_fighting(me))
		attacker->receive_curing("sen", damage);	//��Ѫ���˷�

	message_vision(RED"$N���ϵ�Ѫ�����ĵ��䡣\n"NOR, me);
	buff["_damage"] -= damage;

	if(random(2) && damage > 500 && ys_buff)		//Ѫ��������Ƴ�����
		BUFF->remove1(ys_buff);

	return 1;
}
