// firefox 2011.12

#include <xyj_x.h>
#include <ansi.h>

inherit F_CLEAN_UP;

#define DURATION		8

string* _msgs = ({
	HIC"$N�������˾����ģ���$nһָ�����һ��������\n"NOR,
	HIR"���$n���㽩Ӳ����Ȼ�������ã�\n"NOR,
	HIR"���$n������һ����\n"NOR
});

int cast(object me, object target)
{
	int dao = me->query_skill("dao", 1);	
	int cost = 50 + me->query("mana_factor");
	int ap, dp;

	target = BTL->get_victim(me, target);

	if(dao < 80) return notify_ok("��ĵ����ɷ�̫�͡�\n");	
	if(!target)	return notify_fail("�����˭��ס��\n");
	if(target->is_busy()) return notify_fail(target->name() + "�Ѿ����������ˣ�\n");
	if(me->query("mana") < cost) return notify_fail("��ķ������㣡\n");

	me->add("mana", -cost);

	ap = me->query("mana_factor") / 8;
	dp = target->query("mana_factor");

	message_vision(_msgs[0], me, target);

	if(random(ap + dp) > dp) {						//  1/9�ɹ���
		message_vision(_msgs[1], me, target);
		target->start_busy(DURATION);
	} else {
		message_vision(_msgs[2], me, target);		
	} 
	me->start_busy(1);

	if(living(target)) target->kill_ob(me);
	return 3;
}

