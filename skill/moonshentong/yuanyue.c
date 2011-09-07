// lifeheal.c

#include <ansi.h>

#define POISON			"moon_poison"

int exert(object me, object target)
{
	int skill = me->query_skill("moonforce", 1);

	if ( !target || target->is_corpse()) 
		return notify_fail("������˭���ʴ���䣿\n");
	if (!target->query_condition(POISON))
		return notify_fail("û��ʴ����Ϲ����ʲô��\n");
	if( me->is_fighting() || target->is_fighting())
		return notify_fail("ս�����޷��˹����ˣ�\n");

	if( me->query("force") - me->query("max_force") <  600 )
		return notify_fail("�������������\n");

	if ( me->query_skill("force") < 100 || skill < 80)
		return notify_fail("����ڹ���Ϊ���������˽��ʴ���䡣\n");

	message_vision(HIY"$N��������ĬĬ��������������Խ��Խ��ͣ�ȫ����������ʥ��Ĺ�ԡ�\n\n"NOR,	me);

	if (random(skill - 60) > 10) {
		target->apply_condition(POISON, 0);
		message_vision(HIY"$N���н����е�ƽ�Ͱ��������������һ�������������۾���\n"NOR, target);
	} else {
		message_vision(HIY"$NͻȻ��ɫ�԰ף��ƺ�������֧����Ż��һ��Ѫ������\n"NOR, me);
	}

	target->receive_cuiring("kee", 10 + me->query_skill("force") / 3);
	me->add("force", -150);
	
	return 1;
}
