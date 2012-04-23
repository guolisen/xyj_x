
#include <ansi.h>

string* _msg = ({
	"脸上露出愉快的微笑。",
	"正躲在一边幸灾乐祸地笑。",
	"脸上露出狡诈的神情，大概又想到了什么坏主意了。",
	"正在绷着个脸扮酷。",
	"捧着肚子笑得前仰后合。",
	"眉头紧锁，不知在想什么心事。",
	"正托着腮帮子作沉思状。",
	"咬牙切齿，一副愤愤不平的样子。",
	"一脸的迷茫，不知道周围发生了什么事。",
	"正在咧着嘴傻乐。",
	"正作天真状。",
	"正在闷闷不乐。",
	"骄傲地昂着头，满脸不屑的神情。",
	"痛苦得呲牙咧嘴，大概是牙痛得厉害。",
	"正强颜欢笑，但掩饰不住心里的哀伤。",
	"正在眉飞色舞。",
	"一脸的尴尬相。",
	"脸上露出灿烂的笑容。",
	"笑得比哭还难看。",
	"正强忍着不让自己哭出来。",
	"媚眼如丝。",
	"正作小鸟依人状。",
	"开怀大笑，露出满嘴的金牙。",
});

int main(object me, string arg)
{
	object who = arg ? present(arg, environment(me)) : 0;

	if(!who || !living(who) || who == me)
		return notify_fail("你想查看谁？\n");
	else {
		string msg = _msg[random(sizeof(_msg))];
		int spell1 = me->query_skill("spells");
		int spell2 = who->query_skill("spells");	
		string str;

		if(me->is_busy())
			notify_fail("你正忙着。\n");
		if(me->query("mana") < spell1)
			return notify_fail("你的法力不足。\n");

		me->add("mana", -spell1);
		me->start_busy(2);

		if (random(spell1) > spell2 && who->name() != who->query("name")) 
			str = "却见" + who->query("name");
		else
			str = "只见" + who->name();

		tell_object(who, "你一抬头，发现" + me->name() + "正把一道锐利的目光向你投来。\n");
		write("你微一凝神，向" + who->name() + "细细打量过去，" + str + msg + "\n\n");
	}
	return 1;
}

int help(object me)
{
      write(@HELP

指令格式 ： observe <人物> 或
	    observe <人物> [ 2 | 3 | ...] 当有多个同名人物时。

这个指令让你运用法术来观察别的人物，如果你的法术高强，则
可能识破别人的变身术。

其他相关指令： bian
HELP
     );
     return 1;
}


