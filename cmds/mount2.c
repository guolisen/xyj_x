// firefox 04/10/2012

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object env = environment(me);
	object r1 = me->query_temp("ridee");
	object rider = ridee->query_temp("rider");
	
	if(!arg || !env || !(ridee = present(arg, env)) || !ridee->query("ride"))
		return notify_fail ("你想骑什么？\n");
	
	if(me->close_to(r1)) return notify_fail("你已经" + r1->ridee_msg() + "了！\n");
	
	me->dismount(1);	//清理无效的骑乘数据

	if(rider) return notify_fail(ridee->name() + "上已有人了！\n");
	
	if(ridee->query("owner") != me->query("id"))				//todo:玩家变坐骑	ridee->query("ride/need_train") && 
		return notify_fail("你需要先驯服" + ridee->name() + "才能去骑它。\n");

	me->mount(ridee)
	message_vision("$N一个纵身，稳稳地%s！\n", me, ridee->ridee_msg());

	return 1;
}

int help(object me)
{
    write(@HELP
指令格式 : mount <坐骑名称>

这个指令可以让你骑到坐骑身上。

HELP
);
  return 1;
}