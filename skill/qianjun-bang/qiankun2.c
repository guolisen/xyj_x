#include <ansi.h>

inherit SSERVER;


mapping _action = ([
	"name"		: "Ǭ��һ��",
	"action"	:
		"$N������$wӭ��һ�ӣ��ó���ǧ��Ӱ�������������߾ٹ�����\n"
		"$w��׼$n�����ž�������ȥ����һ��Ҫ�Ǵ��У����������޽���Ҳ����һ��",
	"parry"		: -50,
	"dodge"		: -50,
	"damage"	: 200,
	"damage_type":  "����"
]);

int perform(object me, object target)
{
	int skill = me->query_skill("qianjun-bang", 1);	
	int cost = 100 + me->query("force_factor");
	int damage = me->query_skill("wuxiangforce", 1) / 5;

	if(!target) target = offensive_target(me);

	if(!target || !me->is_fighting(target))	return notify_fail("��Ǭ��һ����ֻ����ս����ʹ�ã�\n");
	if(skill < 120)	return notify_fail("���ǧ�������𻹲�����\n");
	if(me->query("force") < cost) return notify_fail("����������㣡\n");
	

	if(!cd_start(me, "im_pfm", 2))
		return notify_fail("�����õ�̫��̫�ľͲ����ˡ�\n");

	me->add("force", -cost);

	message_vision(HIC"\n$N���㾫��һ�������ڿգ�ʹ���ˡ�Ǭ��һ�����ľ�����\n"NOR,me);

	if(!userp(me) || me->query("betray/count")) damage = 0;
	me->add_temp("apply/damage", damage);
	trace("damage:" + damage);
	me->set("actions", _action);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	me->reset_action();

	me->add_temp("apply/damage", -damage);
		
	if(!target->is_fighting(me)) {
		if( living(target) ) {
			if( userp(target) ) target->fight_ob(me);
			else target->kill_ob(me);
		}
	}

	me->set_temp("no_move", 1);
	call_out("remove_no_move", 1, me);
	return 1;
}

void remove_no_move(object me) {
	if (me) me->delete_temp("no_move");
}
