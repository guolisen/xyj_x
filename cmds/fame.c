// by firefox 04/10/2010
// 声望

#include <ansi.h>
#include <xyj_x.h>

inherit F_CLEAN_UP;

#define FAME_D		"/adm/daemons/schemed"

int main(object me, string arg)
{
	object who = me;
	if(arg) {
		who = find_player(arg);
		
		if(!wizardp(me)) return notify_fail("你无权查看他人声望。\n");

		if(!who)	return notify_fail("没有这个玩家。\n");
	}

	return FAME_D->show(who);
}



int help (object me)
{
	write(@HELP
指令格式 : fame [<玩家>]

列出玩家各个阵营的声望。

HELP );
        return 1;
}
