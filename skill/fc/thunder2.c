// firefox 2011.12

#include <ansi.h>

inherit F_CLEAN_UP;

int cast(object me, object target)
{
	return SPELL_D->do_cast(
		me, 
		target, 
		120,
		120 - 20,
		"sen",
		HIC"\n$N�������˾����ģ�����߳�λ��ͷӥ�ǵ��׹�������ִ����������׶����׶�������$n��ͷ��ը��һƬ���ף�\n"NOR,
		HIR"\n���$n�����������ð���ǣ����񲻶����������ڵأ�\n"NOR,
		HIC"\n˭֪$n���޷�Ӧ�����������Ƶġ�\n"NOR,
		HIC"�����׹���$n�Է���һ����һ��ʧ��֮�����׶�ը����$N��ͷ����\n"NOR,
		HIC"���$n�����������ð���ǣ����񲻶����������ڵأ�\n"NOR,
		25,
		2 - 2,
		4
	);
}
