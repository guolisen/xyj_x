// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>

int main(object me, string arg)
{
	if(!arg) {
		if(me->is_busy()) return notify_ok("你现在正忙着呢。\n");
		if(me->is_fighting()) return notify_ok("你正在打架，自顾不暇。\n");

		me->remove_all_killer();
		write("你心中默念一个『"HIG"恕"NOR"』字，一切冤仇抛诸脑后。\n");
		me->start_busy(10);
	} else {
		object target = present(arg, environment(me));
		string callname;
		if(environment(me)->query("no_fight")) return notify_fail("这里不准战斗。\n");
		if(!objectp(target)) return notify_fail("这里没有这个人。\n");
		if(!BTL->can_attack(me, target)) return notify_fail("你想杀谁？\n");
		
		callname = RANK_D->query_rude(target);
		if(me->is_killing(target->query("id"))) {
			write("\n你对着" + target->name() + "喝道：「" + callname + "！今日不是你死就是我活！」\n\n");
			me->kill_ob(target);
			return 1;
		}
		message_vision("\n$N对着$n喝道：「"
			+ callname + "！今日不是你死就是我活！」\n\n", me, target);

		if(target->query_temp("protected")) {
			object guard = present(target->query_temp("protect_ob"), environment(target));
			if(objectp(guard) && guard != me
				&& guard->query_temp("protect") == target->query("id"))
			{
				message_vision(HIC"$N对着$n大声说：有我在此，不用担心！\n"NOR, guard, target);
				message_vision(HIC"$N冲上前去挡住了$n的攻击。\n"NOR, guard, me);
				guard->kill_ob(me);
				me->kill_ob(guard);
			}
		}
		me->kill_ob(target);
		if(userp(target)) target->fight_ob(me);
		else target->kill_ob(me);
	}
	return 1;
}

int help(object me)
{
  write(@HELP
指令格式 : kill <人物>
 
这个指令让你主动开始攻击一个人物，并且□试杀死对方，kill 和 fight 最大的
不同在于双方将会真刀实枪地打斗，也就是说，会真的受伤。由于 kill 只需单方
面一厢情愿就可以成立，因此你对任何人使用 kill 指令都会开始战斗，通常如果
对方是 NPC 的话，他们也会同样对你使用 kill。

当有人对你使用 kill 指令时会出现红色的字样警告你，对于一个玩家而言，如果
你没有对一名敌人使用过 kill 指令，就不会将对方真的打伤或杀死( 使用法术除
外)。

其他相关指令: fight

有关 fight 跟 kill 的区分请看 'help combat'.
HELP
    );
    return 1;
}

