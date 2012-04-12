
#include <skill.h>
#include "/cmds/std/valid_kill.h";

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object env = environment(me);
	string perf;

	seteuid(getuid());

	if(me->is_busy()) return notify_fail("( ����һ��������û����ɣ�����ʩ���⹦��)\n");
	if(!arg) return notify_fail("��Ҫ���⹦��ʲô��\n");
	if(env->query("no_fight")) return notify_fail("���ﲻ��ʩ���⹦��\n");
	if(me->query("no_attack")) return notify_fail("�㻹����ʩ���⹦��\n");

	if(sscanf(arg, "%s on %s", perf, arg) == 2) {
		object target = present(arg, env);
		if(!target) return notify_fail("����û�� " + arg + "��\n");
		if(!valid_kill(me, target, 0)) return 0;
		arg = perf + " " + arg;
	}
	{
		object weapon = me->query_temp("weapon");
		string martial = weapon ? weapon->query("skill_type") : "unarmed";
		string skill = me->query_skill_mapped(martial);
		if(stringp(skill)) {
			trace("arg:" + arg);
			if(SKILL_D(skill)->perform_action(me, arg))	return 1;
			if(SKILL_D(martial)->perform_action(me, arg)) return 1;
			return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
		}
	}
	return notify_fail("�������� enable ָ��ѡ����Ҫʹ�õ��⹦��\n");
}



int help (object me)
{
        write(@HELP
ָ���ʽ��perfrom [<�书����>.]<��ʽ����> [<ʩ�ö���>]

�������ѧ���⹦(ȭ�š�����������....)��һЩ����Ĺ�����ʽ����ʽ������
�����ָ����ʹ�ã���������� enable ָ��ָ����ʹ�õ��书����ָ���书��
��ʱ�����ֵ��⹦��ָ���ȭ�Ź���ʹ������ʱ���Ǳ��е��书��


���仰˵��ֻҪ�� enable �е��书��������ʽ�ģ������������ָ��ʹ�á�
HELP
        );
        return 1;
}
