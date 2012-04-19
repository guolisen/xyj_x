// firefox 04/10/2012

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ridee = me->dismount()
	if(!ridee) return notify_fail ("你没有坐骑。\n");
	message_vision("$N挺身从$n上跃下来。\n", me, ridee);    
	return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : dismount <坐骑名称>

这个指令可以让你从坐骑上下来。

HELP
);
  return 1;
}
