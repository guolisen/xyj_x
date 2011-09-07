// by firefox 04/10/2010
// 导师命令

#include <ansi.h>
#include <xyj_x.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object g = GANG->of(me);
	object token = present("gang token", me);
	string str;

	seteuid(getuid());

	if(!token) {
		token = new_to(GANG_DIR"_lib/token", me);
		if(token) tell_object(me, CYN"有件东西落入你的怀中。\n\n"NOR);
	}

	if(!arg || arg == "list") return GANG->list();

	//请求加入帮会
	if(sscanf(arg, "join %s", str) == 1) {
		if(g) return notify_fail("你已经加入帮会。\n");
		g = GANG_GET(str);
		if(!g) return notify_fail("帮会不存在。\n");
		return g->join(me);
	}

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

	//某人因为热心帮助xx在玩家中的声望提高了。
	//修改配额，记录玩家消耗的总配额

	return notify_fail("无效的命令参数。\n");
}

int help(object me)
{
	write("
指令格式 : tutor | daoshi [<子命令>] [<参数>]

帮会命令，通过子命令查看，管理帮会，子命令如下：

list                  列出所有导师及其学生
first sb.             设定第一个导师，也就是进站介绍人
set sb.               设置导师

");
        return 1;
}

