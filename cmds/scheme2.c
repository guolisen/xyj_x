// scheme.c

#include <ansi.h>
#include <xyj_x.h>

inherit F_CLEAN_UP;

#define SCHEME_D		"/adm/daemons/schemed"

int main(object me, string arg)
{
	string schedule = me->query("schedule");

	seteuid(getuid());

	if(!arg) return SCHEME_D->show(me);

	if(sscanf(arg, "show %s", arg) == 1) {
		object ob = find_player(arg);
		
		if(!wizardp(me))
			return notify_fail("你无权查看他人制订的计划。\n");

		if(!ob)
			return notify_fail("没有这个玩家。\n");

		return SCHEME_D->show(ob);
	}

	if(arg == "clear") return SCHEME_D->clear(me);

	if(arg == "edit") return SCHEME_D->edit(me);

	if(arg == "start") return SCHEME_D->start(me);

	if(arg == "stop") return SCHEME_D->stop(me);

	if(wizardp(me) && arg == "list") return SCHEME_D->list();

	return notify_fail("非法的命令参数。\n");
}



int help (object me)
{
	write(@HELP
指令格式 : scheme [<edit> | <start> | <clear> | <show> <玩家>]
 
设定或开始你的计划。如果你需要长时间的读书或是练习技能，可以
使用计划来完成，具体请参见 help schedule。

edit  : 设定计划
start : 开始执行计划
stop  : 停止执行计划
clear : 清除目前的计划
show  : 显示某个玩家的计划，只有巫师才能使用这个命令。

HELP );
        return 1;
}
