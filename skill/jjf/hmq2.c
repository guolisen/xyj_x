//by pkyou@DHXYII 2002/5/7
//���ƽ���������ǹ��֮����ǹ��

// Ҫ�㣺������Ѫ�ȣ���³ç��cor��,������cps��,����?��exp��

inherit SSERVER;

#include <ansi.h>

#define CD					60

int perform(object me, object target)
{                             
	object weapon = me->query_temp("weapon");	
	object ridee = me->ride();
	int spear = me->query_skill("spear");
	int skill2 = spear + me->query_skill("dodge");
	string msg;
	int success = 0;

	if(me->query("family/family_name") != "������"  || me->query("betray/count"))
		return notify_ok("�����Ķ�͵ѧ�����书��Ҳ���û���ǹ?\n");

	if(!target) target = offensive_target(me);
	if(!target || !me->is_fighting(target) || !living(target))
		return notify_ok(HIW"��ֻ����ս����ʹ�á�\n"NOR);

	if(!ridee)
		return notify_ok("����ǹ��Ҫ������ϡ�\n");

	if(me->query_temp("no_move") || ridee->query_temp("no_move"))	//�ƽ⡺����ǹ��
		return notify_ok("�㶯���ˣ�û��թ�ܣ�\n");

	if(target->is_busy() || target->query_temp("no_move"))			//�ƽ⡺����ǹ��
		return notify_ok("�Է���ʱû�����㣬��թ���ˣ�\n");
	
	if(skill2 < 200)
		return notify_ok("���ǹ�����������ã�����ʡʡ�ɣ�\n");

	if(me->query("force") < 500)
		return notify_ok("���������ã��ֽŷ�����ǹ���ò��ȡ�\n");

	if (target != me->query_temp("last_damage_from")) 
		return notify_ok("�Է���δ���㣬�ο��´˺��֡�\n");

	if(!cd_start(me, "hmq", CD))
		return notify_ok("�յ�֮�Ʋ������ã�����û�˻����ˡ�\n");

	me->add("force", -300);

	msg = CYN"$N���һǹ������ߣ�";

	{
		//������Ѫ��
		int r1 = 100 * me->query("eff_kee") / (10 + me->query("max_kee"));
		int r2 = 100 * target->query("eff_kee") / (10 + target->query("max_kee"));

		//³ç�̶�
		int n1 = me->query("cor") - me->query("cps");
		int n2 = target->query("cor") - target->query("cps");

		//��/ǹ�����������м�
		int d1 = skill2 / 2;						//ǹ������
		int d2 = target->query_skill("dodge");		//��

		if(d2 < 1) d2 = 1;

		trace("r1:" + r1 + "  r2:" + r2 + "  n1:" + n1 + "  n2:" + n2);

		success = r2 - r1 + (n2 - n1) + (d1 * 10 / d2);
		trace("success:" + success);

		success = success > random(100);
	}

	if(!success) {
		message_vision(msg + "$nΨ����թ���ɲ�����δ�������\n"NOR, me, target);
		call_out("remove_no_move", 1, target);	//����׷��ԭ��̤��
	} else {

		int damage = me->query_str() * me->query_temp("apply/damage") / 10;

		message_vision(msg + "$n��׷���ᡣ\n"NOR, me, target);
		message_vision(HIC"$n�ۼ�Ҫ����$N���������У��䲻��$N�����̣�ֱָ�ʺ�\n"NOR, me, target);

		trace("damage:" + damage);
		target->receive_damage("kee", damage, me);
		target->receive_wound("kee", damage, me);

		COMBAT_D->report_status(target);

		me->start_busy(1);
		target->start_busy(1);		//�Ż���
	}
	return 1;
}

void remove_no_move(object who)
{
	if(who) who->delete_temp("no_move");
}
