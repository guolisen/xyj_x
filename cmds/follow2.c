
inherit F_CLEAN_UP;

int main(object me, string arg)
{	
	if(!arg) return notify_fail("ָ���ʽ��follow <ĳ��>|none��\n");

	if(arg == "none") {
		me->set_leader(0);
		write("Ok.\n");
	} else {
		object ob = present(arg, environment(me));

		if(!objectp(ob))
			return notify_fail("����û�� " + arg + "��\n");
		if(!ob->is_character())
			return notify_fail("ֻ�ܸ�����\n");
		if(ob == me)
			return notify_fail("���ܸ����Լ���\n");

		me->set_leader(ob);
		tell_object(me, "�������ʼ����" + ob->name() +"һ���ж���\n");
		if (ob->visible(me)) 
			tell_object(ob, me->name() + "������ʼ������һ���ж���\n");
	}
	return 1;
}

int help (object me)
{
	write(@HELP
ָ���ʽ : follow|gen [<����>|none]

���ָ�������ܸ���ĳ�˻����
������� follow none ��ֹͣ���档

HELP
	);
	return 1;
}
