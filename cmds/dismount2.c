// firefox 04/10/2012

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ridee = me->dismount()
	if(!ridee) return notify_fail ("��û�����\n");
	message_vision("$Nͦ���$n��Ծ������\n", me, ridee);    
	return 1;
}

int help(object me)
{
    write(@HELP
ָ���ʽ : dismount <��������>

���ָ����������������������

HELP
);
  return 1;
}
