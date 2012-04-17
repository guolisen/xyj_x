
inherit F_CLEAN_UP;

int do_wield(object me, object ob);

int main(object me, string arg)
{
	object ob;

	if(!arg) return notify_fail("��Ҫװ��ʲô������\n");

	if(arg == "all") {
		foreach(ob in all_inventory(me)) {		
			if(ob->query("equipped")) continue;
			do_wield(me, ob);
		}
		write("Ok.\n");
		return 1;
	}

	if(!objectp(ob = present(arg, me)))
		return notify_fail("������û������������\n");

	if(ob->query("equipped"))
		return notify_fail("���Ѿ�װ�����ˡ�\n");

	return do_wield(me, ob);
}

int do_wield(object me, object ob)
{	
	if(me->query_temp("no_wield"))
		return notify_fail("�����ڲ��ܳ��б�����\n");

	if(ob->wield()) {
		string str = or2(ob->query("wield_msg"), "$Nװ��$n��������\n");
		message_vision(str, me, ob);
		return 1;
	} else
		return 0;
}

int help(object me)
{
	write(@HELP
ָ���ʽ��wield|zhuangbei <װ������>
 
���ָ������װ��ĳ����Ʒ������, �����Ҫӵ��������Ʒ.
 
HELP
    );
    return 1;
}
