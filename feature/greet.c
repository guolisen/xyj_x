
#include <xyj_x.h>
#include <ansi.h>

//¼ûÃæÎÊºò
varargs void greet(object me, object who, mixed msg, int delay)
{
	delay = max2(delay, 1);
	if(msg && interactive(who) && !me->is_fighting()) {
		remove_call_out("greet_");
		call_out("greet_", delay, me, who, msg);
	}
}

private void greet_(object me, object who, mixed msg)
{
	if(!same_env(me, who)) return;
	if(stringp(msg)) message_vision(msg + NOR"\n", me, who);
	if(functionp(msg)) evaluate(msg, me, who);
}

