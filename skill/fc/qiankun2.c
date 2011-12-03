// firefox 2011.12
#include <ansi.h>
#include <xyj_x.h>

#define RESERVE_FORCE			5
#define EFF_DURATION			8

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

///�����Ч�Ĵ���
void check_eff(object me, object target)
{
	int ap = me->query_str();
	int dp = target->query_str();

	if(me->query_temp("last_damage_from") == target) ap += ap / 3;	//���˶���ŭ

	if(random(ap) > dp) {
		message_vision(HIC"\n$n��$NӲ����������¶������ã�\n"NOR, me, target);
		BTL->start_no_move(target, EFF_DURATION);
	}
}

int perform(object me, object target)
{
	int enhance = me->query_skill("wuxiangforce", 1) / 3;

	object weapon = me->query_temp("weapon");
	int skill = me->query_skill("qianjun-bang", 1);	
	int cost = 100 + me->query("force_factor");

	target = BTL->get_victim(me, target);

	if(!target || !me->is_fighting(target))	return notify_fail("��Ǭ��һ����ֻ����ս����ʹ�ã�\n");
	if(skill < 120)	return notify_fail("���ǧ�������𻹲�����\n");
	if(me->query("force") < cost) return notify_fail("����������㣡\n");
	if(!cd_start(me, "im_pfm", 2)) return notify_fail("�����õ�̫��̫�ľͲ����ˡ�\n");

	me->add("force", -cost);

	message_vision(HIC"\n$N���㾫��һ�������ڿգ�ʹ���ˡ�Ǭ��һ�����ľ�����\n"NOR,me);

	if(!BTL->loyal_member(me, "����ɽ���Ƕ�")) enhance = 0;
	if(!cd_start(me, "reserve_force", RESERVE_FORCE)) enhance = 0;

	me->add_temp("apply/strength", enhance);
	me->set("actions", _action);
	if(COMBAT_D->do_attack(me, target, weapon) > 0 && enhance > 0) check_eff(me, target);
	me->reset_action();
	me->add_temp("apply/strength", -enhance);
		
	BTL->fight_enemy(target, me);

	BTL->start_no_move(me, 1);
	return 1;
}
