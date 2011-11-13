// firefox 11/11/2011

#include <xyj_x.h>

inherit F_CLEAN_UP;

int follow_sb(object me, object who)
{
	if(who == me) return notify_fail("���ܸ����Լ���\n");
	me->set_leader(who);
	tell_object(me, "�������ʼ����" + who->name() +"һ���ж���\n");
	if(who->visible(me)) 
		tell_object(who, me->name() + "������ʼ������һ���ж���\n");
	return 1;
}

int main(object me, string arg)
{
	if(!arg) return notify_fail("ָ���ʽ��follow <ĳ��>|none��\n");

	if(arg == "none") {
		me->set_leader(0);
		write("Ok.\n");
	} else {
		int for_guard = sscanf(arg, "-g %s", arg) == 1;
		object who = (arg == "me") ? me : present(arg, environment(me));

		if(!objectp(who))
			return notify_fail("����û�� " + arg + "��\n");
		if(!who->is_character())
			return notify_fail("ֻ�ܸ�����\n");

		if(for_guard) {
			foreach(object ob in GUARD->gards(me)) {
				follow_sb(ob, who);
			}
			return notify_ok("OK.\n");
		}
		return follow_sb(me, who);
	}
	return 1;
}

int help (object me)
{
	write(@HELP
ָ���ʽ : follow|gen [-g] [<����>|me|none]

���ָ�������ܸ���ĳ�˻��������-g����ָʾ������
������� follow none ��ֹͣ���档

HELP
	);
	return 1;
}
