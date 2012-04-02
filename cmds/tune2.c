// tune.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string *tuned_ch = me->query("channels");

	if(!arg) {
		if( !pointerp(tuned_ch) || !sizeof(tuned_ch) )
			write("�����ڲ�û�������κ�Ƶ����\n");
		else
			write("������������Ƶ����" + implode(tuned_ch, ", ") + "��\n");
		return 1;
	}

	if(arg == "all") {
		me->set("channels", 0);
		write("�ر�������ͨ����\n");
	}
	else if( pointerp(tuned_ch) && member_array(arg, tuned_ch) != -1 ) {
		write("�ر� " + arg + " Ƶ����\n");
		tuned_ch -= ({ arg });
		me->set("channels", tuned_ch);
	} else {
		write("Ҫ��ĳ��Ƶ��ֻҪ�ø�Ƶ��˵�����ɡ�\n");

	}
	return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ��tune [<Ƶ������>|all]

���ָ������ѡ���Ƿ�Ҫ����ĳһƵ����ѶϢ�����û��ָ��Ƶ�����ƣ��ͻ��г�
��Ŀǰ�����е�Ƶ�������ָ����Ƶ����ԭ�������еľͻ�ص�����֮�򿪡�
����all���ر�����Ƶ����������һ��û�������е�Ƶ�����������Զ������򿪡�
Ҫ��һ��Ƶ��������ֻҪ�ã�

<Ƶ������> <ѶϢ> ....

���ӣ�
  chat hello everyone!
  
������� help channels ��ѯĿǰ����ЩƵ������������

see also : shout
HELP
        );
        return 1;
}
