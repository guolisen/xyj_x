// firefox 2012.4

#include <ansi.h>

#define POISON			"moon_poison"

int exert(object me, object target)
{
	int skill = me->query_skill("moonforce", 1);
	int duration, cost;

	if(!target || target->is_corpse()) 
		return notify_fail("������˭���ʴ���䣿\n");

	duration = target->query_condition(POISON)
	if (duration > 0) return notify_fail("Ŀ��û��ʴ���䡣\n");

	if(me->is_fighting() || target->is_fighting())
		return notify_fail("ս�����޷��˹����ˣ�\n");

	cost = duration * 100;
	if(me->query("force") < cost) return notify_fail("����������㡣\n");

	message_vision(HIY"$N��������ĬĬ��������������Խ��Խ��ͣ�ȫ����������ʥ��Ĺ�ԡ�\n\n"NOR,	me);

	me->add("force", -cost);
	if(random(skill) > duration) {
		message_vision(HIY"$N���н����е�ƽ�Ͱ��������������һ�������������۾���\n"NOR, target);

		target->apply_condition(POISON, 0);
		target->receive_cuiring("kee", 10);
	} else {
		message_vision(HIY"$NͻȻ��ɫ�԰ף��ƺ�������֧����Ż��һ��Ѫ������\n"NOR, me, target);
	}
	
	return 1;
}
