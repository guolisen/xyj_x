// cracked by vikee 2/09/2002   vikee@263.net
// enchant.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int max_pts = me->query_skill("spells")/2;
	int pts;

	if(arg == "max")
		pts = max_pts;
	else if(!arg || !sscanf(arg, "%d", pts)) 
		return notify_fail("ָ���ʽ��enchant <��������>|max\n");

	if( pts > max_pts )
		return notify_fail("��ķ������㣬��������ôǿ��������\n");

	if( pts < 0 ) return notify_fail("��������������������\n");	
	me->set("mana_factor", pts);
	write("Ok.\n");
	return 1;
}

int help (object me)
{
	write(@HELP
ָ���ʽ: enchant <��������>|max
 
���ָ�������趨ʹ��ħ������ʱҪ������������ħ�����õķ���ǿ�ȡ�
��������Խ�ߣ�ħ��������ɱ����ҲԽǿ��

HELP
	);
	return 1;
}
