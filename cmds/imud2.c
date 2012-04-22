// firefox 04/20/2012

#include <xyj_x.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if(!arg || arg == "list") return IMUD->list();

	if(arg == "go") return IMUD->go();
	if(arg == "back") return IMUD->back();

	//设置帮会领袖
	if(wizardp(me) && sscanf(arg, "leader %s %s", str, arg) == 2) {
		g = GANG_GET(str);
		if(!g) return notify_fail("帮会不存在。\n");
		return g->leader(find_player(arg));
	}

	if(!g) return notify_fail("你还不属于任何帮会。\n");

	if(arg == "who") return g->who();

	if(arg == "quit") return g->quit(me);
	
	if(sscanf(arg, "accept %s", arg) == 1)
		return g->accept(me, find_player(arg));

	if(sscanf(arg, "promote %s", arg) == 1)
		return g->promote(me, find_player(arg));

	if(sscanf(arg, "demote %s", arg) == 1)
		return g->demote(me, find_player(arg));

	if(sscanf(arg, "title %s %s", arg, str) == 2)
		return g->title(me, find_player(arg), str);

	return notify_fail("无效的命令参数。\n");
}

int help(object me)
{
	write("
指令格式 : gang | bang [<参数>]

互联泥潭命令，参数如下：

list                  列出互联泥潭战绩
go                    前往互联泥潭
back                  回到原来的MUD位置

");
        return 1;
}

