// by firefox 02/09/2010

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

int perform(object me, object target)
{
	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("耙谁？\n");

	message_vision(HIW"\n$N身形展动,仿佛水神一般舞动着手中耙,正是种猪绝技［疯猪二百耙］！\n\n"NOR,me,target);
	
	for(int i = 1; i < 12; ++i) {
		message_vision(HIC"$N试图使出[疯猪二百耙]的［第"+chinese_number(i)+"耙］，但是被对手打断了！\n"NOR, me, target);
	}
	message_vision("......\n\n", me);
	for(int i = 198; i < 201; ++i) {
		message_vision(HIC"$N试图使出[疯猪二百耙]的［第"+chinese_number(i)+"耙］，但是被对手打断了！\n"NOR, me, target);
	}

	message_vision(HIY"\n$N绝招用毕,停下身形,周围也顿时恢复了平静.$n却依然在数耙子.\n\n"NOR, me, target);
	me->command("haha " + target->query("id"));
	me->command("say 小样儿，就算打不着你，我也要flood晕你。");
	me->start_busy(3);
	if(!target->is_busy()) target->start_busy(3);
	return 1;
}





