
#include <skill.h>
#include "/cmds/std/valid_kill.h";

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object env = environment(me);
	string perf;

	seteuid(getuid());

	if(me->is_busy()) return notify_fail("( 你上一个动作还没有完成，不能施用外功。)\n");
	if(!arg) return notify_fail("你要用外功做什么？\n");
	if(env->query("no_fight")) return notify_fail("这里不能施用外功。\n");
	if(me->query("no_attack")) return notify_fail("你还不能施用外功。\n");

	if(sscanf(arg, "%s on %s", perf, arg) == 2) {
		object target = present(arg, env);
		if(!target) return notify_fail("这里没有 " + arg + "。\n");
		if(!valid_kill(me, target, 0)) return 0;
		arg = perf + " " + arg;
	}
	{
		object weapon = me->query_temp("weapon");
		string martial = weapon ? weapon->query("skill_type") : "unarmed";
		string skill = me->query_skill_mapped(martial);
		if(stringp(skill)) {
			trace("arg:" + arg);
			if(SKILL_D(skill)->perform_action(me, arg))	return 1;
			if(SKILL_D(martial)->perform_action(me, arg)) return 1;
			return notify_fail("你所使用的外功中没有这种功能。\n");
		}
	}
	return notify_fail("你请先用 enable 指令选择你要使用的外功。\n");
}



int help (object me)
{
        write(@HELP
指令格式：perfrom [<武功种类>.]<招式名称> [<施用对象>]

如果你所学的外功(拳脚、剑法、刀法....)有一些特殊的攻击方式或招式，可以
用这个指令来使用，你必须先用 enable 指令指定你使用的武功，不指定武功种
类时，空手的外功是指你的拳脚功夫，使用武器时则是兵刃的武功。


换句话说，只要是 enable 中的武功有特殊招式的，都可以用这个指令使用。
HELP
        );
        return 1;
}
