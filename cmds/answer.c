// by firefox 11/21/2009
// npc��������ʣ����Ӧ��

#include <xyj_x.h>
#include <ansi.h>

inherit F_CLEAN_UP;

#define PROP				"question"

//�ش�Ŀ�귢��
int main(object me, string arg)
{
	mapping m = me->query_temp(PROP);
	if(m && same_env(me, m["npc"])) {
		if(!arg) notify_fail("��Ҫ�ش�ʲô��\n");

		message_vision(CYN"$N�ش�$n����"NOR, me, m["npc"]);

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

//����
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

