// by pkyou@xyj

//���μǲ��˹���ͻ������������pkyou��ԭ�����Ҹĵ���Ŀȫ���ˡ�
//���¶�λ��ͻ������������ѹ�ƣ��öԷ������ˣ����������мܺ�̽���

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"kaishan"
#define NAME			HIR"�嶡��ɽ"NOR
#define CD				20
#define DURATION		10

int perform(object me, object target)
{
	int enhance = me->query_skill("huomoforce", 1) / 2;
	int stick = me->query_skill("dali-bang", 1);

	mapping req = ([
		"skill1"	: ([ "stick"	: 100 ]),
		"prop"		: ([ "force"	: stick ]),
	]);

	mapping buff = ([
		"id"		: ID,
		"name"		: NAME,
		"comment"	: "�������������",
		"duration"	: DURATION,
		"add_apply" : ([ "strength" : enhance ]),	//������
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("��˭��\n");
	if(!me->is_fighting(target)) return notify_ok("��"NAME"��ֻ����ս����ʹ�á�\n");

	if(!BTL->require(me, NAME, req)) return 1;
	if(!cd_start(me, ID, CD)) return notify_ok("����ʱ����ʹ�á�"NAME"����\n");

	BTL->pay(me, req["prop"]);

	BUFF->add(me, buff);		//��������buff

	msv(HIC"\n$N���һ�����α��ǣ���ͬ�嶡��ʿһ�㣬�������б�����������$n��\n", me, target);
	
	trace("me str:" + me->query_str() + " target str:" + target->query_str());
	//����������������
	if(enhance + me->query_str() > 3 * random(target->query_str())) {
		
		mapping debuff = ([
			"id"		: ID + "ed",
			"name"		: HIR"�����м�"NOR,
			"comment"	: "�������������޷����м��ˡ�",
			"duration"	: DURATION,
			"add_apply" : ([ "parry" : -stick * 2 ]),	//�м����Ƿ���
		]);
		int damage = me->query_str() - target->query_str();
		damage = max2(damage * 4, 50);

		target->receive_damage("kee", damage, me);	//���ˣ����ӻ���
		target->receive_wound("kee", damage, me);
		COMBAT_D->report_status(target);

		BUFF->add(target, debuff);		//����parry debuff

		msv("$n�����мܣ�Ȼ�����в��������������³�һ����Ѫ��\n"NOR, me, target);
	}
	else {
		msv("$n�����мܣ����Ͻ������߽⡣\n"NOR, me, target);
	}
	me->start_busy(1);
	return 1;
}

