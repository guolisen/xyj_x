// firefox 2011.12

#include <ansi.h>
#include <xyj_x.h>

#define CD			5
#define NAME		HIW"��������"NOR

int perform(object me, object target)
{
	object weapon = me->query_temp("weapon");
	int skill = me->query_skill("qianjun-bang", 1);	
	int cost = 50 + me->query("force_factor");

	target = BTL->get_victim(me, target);

	if(!target || !me->is_fighting(target))	return notify_fail("��"NAME"��ֻ����ս����ʹ�ã�\n");
	if(skill < 60)	return notify_fail("���ǧ�������𻹲�����\n");
	if(me->query("force") < cost) return notify_fail("����������㣡\n");
	if(!cd_start(me, "im_pfm", CD)) return notify_fail("����ʱ������ʹ��"NAME"��\n");

	me->add("force", -cost);

	message_vision(HIC"\n$N���㾫������һת��������������$n���������У�\n"NOR, me, target);

	me->set_temp("QJB_perform", 4);
	COMBAT_D->do_attack(me, target, weapon);
	me->set_temp("QJB_perform", 1);
	COMBAT_D->do_attack(me, target, weapon); 
	me->set_temp("QJB_perform", 6);
	COMBAT_D->do_attack(me, target, weapon);
	me->delete_temp("QJB_perform");

	BTL->fight_enemy(target, me);
	BTL->start_no_move(me, 3);

	return 1;
}
