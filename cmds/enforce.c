// cracked by vikee 2/09/2002   vikee@263.net
// enforce.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int max_pts = me->query_skill("force") / 2;
	int pts;

	if(arg == "max")
		pts = max_pts;
	else if( !arg || (arg!="none" && !sscanf(arg, "%d", pts)) ) 
		return notify_fail("ָ���ʽ��enforce <ʹ�����������˵�>|none|max");

	if( !me->query_skill_mapped("force") )
		return notify_fail("������� enable һ���ڹ���\n");

	if( arg=="none" )
		me->delete("force_factor");
	else {
		if( pts < 0 || pts > max_pts )
			return notify_fail("��ֻ���� none ��ʾ���������������ֱ�ʾÿһ���ü���������\n");
		me->set("force_factor", pts);
	}

	write("Ok.\n");
	return 1;
}

int help (object me)
{
        write(@HELP
ָ���ʽ: enforce|jiali <ʹ�����������˵�>|none|max
 
���ָ������ָ��ÿ�λ��е���ʱ��Ҫ�������������˵С�

enforce none ���ʾ�㲻ʹ�������� 

SEE ALSO : enable, enchant
HELP
        );
        return 1;
}
