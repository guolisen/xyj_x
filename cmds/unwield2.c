// cracked by vikee 2/09/2002   vikee@263.net
// unwield.c

inherit F_CLEAN_UP;

int do_unwield(object me, object ob)
{
	string str;
	if( (string)ob->query("equipped") != "wielded")
		return notify_fail("�㲢û��װ������������Ϊ������\n");

	if( ob->unequip() ) {
		if( !stringp(str = ob->query("unwield_msg")) )
			str = "$N�������е�$n��\n";
		message_vision(str, me, ob);
		return 1;
	}
	return 0;
}

int main(object me, string arg)
{
	object ob;
	int i;

	if( !arg ) return notify_fail("��Ҫ�ѵ�ʲô��\n");

	if(arg=="all") {
		foreach(ob in all_inventory(me)) {
			do_unwield(me, ob);
		}
		write("Ok.\n");
		return 1;
	}

	if( !objectp(ob = present(arg, me)) )
		return notify_fail("������û������������\n");

	return do_unwield(me, ob);
}

int help(object me)
{
  write(@HELP
ָ���ʽ : unwield|fangxia <��Ʒ��>|all 
 
���ָ������������е�������
 
HELP
    );
    return 1;
}
 
