
inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string what)
{
	mapping given = ([]);
	int n = 0;

	if(!what) 
		return notify_fail("ָ���ʽ giveip ��Ʒ·��\n");

	if( sscanf(what, "%*s.c") != 1)
		return notify_fail("·�����Ϸ����޷��ҵ���Ʒ��\n");

	if( file_size(what) < 0 )
		return notify_fail("û���������(" + what + ")��\n");    

	seteuid(getuid());

	foreach(object who in users()) {
		object ob;
		string ip = query_ip_number(who);
		if(!ip || given[ip] || !environment(who)) continue;
		ob = new(what);
		if(ob->move(who)) tell_object(who, HIG"����ͻȻ������ʲô��������Ŀڴ��\n" NOR);
		given[ip] = 1;
		n++;
	}

	printf("����%dλ��ҵõ���%s��\n", n, what->query("name"));
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ��giveip ��Ʒ·��

�����ߵ��������һ����Ʒ��ÿIP��һ����

HELP
	);
	return 1;
}