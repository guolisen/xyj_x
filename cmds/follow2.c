
inherit F_CLEAN_UP;

int main(object me, string arg)
{	
	if(!arg) return notify_fail("指令格式：follow <某人>|none。\n");

	if(arg == "none") {
		me->set_leader(0);
		write("Ok.\n");
	} else {
		object ob = present(arg, environment(me));

		if(!objectp(ob))
			return notify_fail("这里没有 " + arg + "。\n");
		if(!ob->is_character())
			return notify_fail("只能跟随活物。\n");
		if(ob == me)
			return notify_fail("不能跟随自己。\n");

		me->set_leader(ob);
		tell_object(me, "你决定开始跟随" + ob->name() +"一起行动。\n");
		if (ob->visible(me)) 
			tell_object(ob, me->name() + "决定开始跟随你一起行动。\n");
	}
	return 1;
}

int help (object me)
{
	write(@HELP
指令格式 : follow|gen [<生物>|none]

这个指令让你能跟随某人或生物。
如果输入 follow none 则停止跟随。

HELP
	);
	return 1;
}
