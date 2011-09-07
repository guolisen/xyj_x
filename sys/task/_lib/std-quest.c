// by firefox 04/20/2010
// 用于替换/std/quest.c

inherit F_CLEAN_UP;

#include <xyj_x.h>

#include <ansi.h>
#include <dbase.h>
#include <origin.h>

void create()
{
	seteuid(getuid());
}

int quest_give(object me, object who, object ob)
{
	return TASK->done_task(me, "give", who, ob);
}

//要返回感谢信息
string quest_ask(object me, object who, string topic)
{
	return TASK->do_ask(me, who, topic);
}

void quest_kill(object me)
{
	object killer = me->query_temp("last_damage_from");
	if(killer) TASK->done_task(killer, "kill", me);
}
