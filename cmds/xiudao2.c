
#include <xyj_x.h>
#include <ansi.h>

inherit F_CLEAN_UP;

#define ID							"xiudao"
#define NAME						"修道"
#define DURATION					60			//单次时间
#define DX_GAIN						3100		//300 spells，3年/小时，72年/天


int gain(int spells)
{
	return DURATION * DX_GAIN * spells / 300 / 3600;
}

int before_reward(mapping buff)
{
	object me = buff["me"];
	int base_dx = gain(150);
	int dx = gain(me->query_skill("spells"));
	int dx1 = dx - base_dx;						//超过基础收益部分要扣配额;
	int xiudao_room = environment(me)->query("xiudao_room");
	
	if(xiudao_room && TASK->query_norm(me) > dx1)
		TASK_EXC->do_reward(me, "自己", "修道", ([ DEXP : dx1 ]));
	else
		dx = min2(dx, base_dx);
	me->add("daoxing", dx);
}

int main(object me, string arg)
{
	return start_xiu(ID,
		NAME,
		DURATION,
		HIY"$N闭上眼睛，盘膝坐下，嘴里默默念念不知在说些什么。\n"NOR,
		HIY"$N缓缓睁开眼睛，长舒一口气站了起来。\n"NOR,
		0,
		(["kee" : 20, "sen" : 20]),
		0,
		(["spells" : 1])
		0,
		(: before_reward :)
	);
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

