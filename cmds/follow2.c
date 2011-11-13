// firefox 11/11/2011

#include <xyj_x.h>

inherit F_CLEAN_UP;

int follow_sb(object me, object who)
{
	if(who == me) return notify_fail("不能跟随自己。\n");
	me->set_leader(who);
	tell_object(me, "你决定开始跟随" + who->name() +"一起行动。\n");
	if(who->visible(me)) 
		tell_object(who, me->name() + "决定开始跟随你一起行动。\n");
	return 1;
}

int main(object me, string arg)
{
	if(!arg) return notify_fail("指令格式：follow <某人>|none。\n");

	if(arg == "none") {
		me->set_leader(0);
		write("Ok.\n");
	} else {
		int for_guard = sscanf(arg, "-g %s", arg) == 1;
		object who = (arg == "me") ? me : present(arg, environment(me));

		if(!objectp(who))
			return notify_fail("这里没有 " + arg + "。\n");
		if(!who->is_character())
			return notify_fail("只能跟随活物。\n");

		if(for_guard) {
			foreach(object ob in GUARD->gards(me)) {
				follow_sb(ob, who);
			}
			return notify_ok("OK.\n");
		}
		return follow_sb(me, who);
	}
	return 1;
}

int help (object me)
{
	write(@HELP
指令格式 : follow|gen [-g] [<生物>|me|none]

这个指令让你能跟随某人或生物。参数-g用于指示护法。
如果输入 follow none 则停止跟随。

HELP
	);
	return 1;
}
