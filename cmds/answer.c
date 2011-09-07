// by firefox 11/21/2009
// npc向玩家提问，玩家应答

#include <xyj_x.h>
#include <ansi.h>

inherit F_CLEAN_UP;

#define PROP				"question"

//回答目标发问
int main(object me, string arg)
{
	mapping m = me->query_temp(PROP);
	if(m && same_env(me, m["npc"])) {
		if(!arg) notify_fail("你要回答什么？\n");

		message_vision(CYN"$N回答$n道："NOR, me, m["npc"]);

		if(functionp(m["anwser"])) {
			evaluate(m["anwser"], me, m["npc"], arg);
		}
		return 1;
	}
}

private void do_answer(object me, object npc, string arg)
{
	npc->do_answer(me, arg);
}

//发问
varargs int ask(object npc, object me, string msg, function fun)
{
	mapping m = ([
		"who"		: me,
		"answer"	: fun ? fun : (: do_answer :),
	]);
	me->set_temp(PROP, m);
	message_vision(CYN + msg + NOR, npc, me);

	return 1;
}

