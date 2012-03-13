
inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string what)
{
	mapping given = ([]);
	int n = 0;

	if(!what) 
		return notify_fail("指令格式 giveip 物品路径\n");

	if( sscanf(what, "%*s.c") != 1)
		return notify_fail("路径不合法，无法找到物品。\n");

	if( file_size(what) < 0 )
		return notify_fail("没有这个档案(" + what + ")。\n");    

	seteuid(getuid());

	foreach(object who in users()) {
		object ob;
		string ip = query_ip_number(who);
		if(!ip || given[ip] || !environment(who)) continue;
		ob = new(what);
		if(ob->move(who)) tell_object(who, HIG"天上突然掉下了什么东西到你的口袋里。\n" NOR);
		given[ip] = 1;
		n++;
	}

	printf("共有%d位玩家得到了%s。\n", n, what->query("name"));
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式：giveip 物品路径

给在线的所有玩家一件物品，每IP限一个。

HELP
	);
	return 1;
}