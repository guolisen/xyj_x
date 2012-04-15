// firefox 04/10/2012

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object env = environment(me);
	object r1 = me->query_temp("ridee");
	object rider = ridee->query_temp("rider");
	
	if(!arg || !env || !(ridee = present(arg, env)) || !ridee->query("ride"))
		return notify_fail ("������ʲô��\n");
	
	if(me->close_to(r1)) return notify_fail("���Ѿ�" + r1->ridee_msg() + "�ˣ�\n");
	
	me->dismount(1);	//������Ч���������

	if(rider) return notify_fail(ridee->name() + "���������ˣ�\n");
	
	if(ridee->query("owner") != me->query("id"))				//todo:��ұ�����	ridee->query("ride/need_train") && 
		return notify_fail("����Ҫ��ѱ��" + ridee->name() + "����ȥ������\n");

	me->mount(ridee)
	message_vision("$Nһ���������ȵ�%s��\n", me, ridee->ridee_msg());

	return 1;
}

int help(object me)
{
    write(@HELP
ָ���ʽ : mount <��������>

���ָ����������ﵽ�������ϡ�

HELP
);
  return 1;
}