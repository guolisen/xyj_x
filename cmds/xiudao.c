
#include <xyj_x.h>
#include <ansi.h>

inherit F_CLEAN_UP;

#define PROP						"sitting"
#define DURATION					60			//单次时间
#define DX_GAIN						3100		//300 spells，3年/小时，72年/天

int main(object me, string arg)
{
	object env = environment(me);

	seteuid(getuid());

	if(env->query("no_fight") || env->query("no_magic"))
		return notify_fail("安全区内禁止练功。\n");

	if(me->is_busy() || me->query_temp(PROP) || me->is_fighting())
		return notify_fail("你现在正忙着呢。\n");

	if(me->query("sen") < 100 || me->query("kee") < 100)
		return notify_fail("你状态不佳，再炼恐怕要走火入魔！\n");

	message_vision(HIY"$N闭上眼睛，盘膝坐下，嘴里默默念念不知在说些什么。\n"NOR, me);

	me->start_busy(DURATION / 2 + 1);
	me->set_temp(PROP, 1);
	call_out("finish", DURATION, me, env->query("xiudao_room"));
	return 1;
}

int gain(int spells)
{
	return DURATION * DX_GAIN * spells / 300 / 3600;
}


void finish(object me, int xiudao_room)
{
	int base_dx = gain(150);
	int dx, dx1;

	if(!me) return;

	dx = gain(me->query_skill("spells"));
	dx1 = dx - base_dx;						//超过基础收益部分要扣配额

	if(xiudao_room && TASK->query_norm(me) > dx1)
		TASK_EXC->do_reward(me, "自己", "修道", ([ DEXP : dx1 ]));
	else
		dx = min2(dx, base_dx);

	me->delete_temp(PROP);

	message_vision(HIY "$N缓缓睁开眼睛，长舒一口气站了起来。\n" NOR, me);

	me->add("daoxing", dx);
	tell_object(me, HIC "你的道行增加了" + chinese_number(dx * 3) + "时辰！\n" NOR);

	me->receive_damage("sen", 20);
	me->receive_damage("kee", 20);
	me->improve_skill("spells", 1 + random(dx) / 10);
}

int help(object me)
{
        write(@HELP
指令格式 : xiudao

静坐修炼以提高道行。
HELP
        );
        return 1;
}


int test()
{
	main(this_player(), 0);
}

