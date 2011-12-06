// firefox 2011.12

#include <xyj_x.h>
#include <ansi.h>

inherit F_CLEAN_UP;

#define DURATION		8

string* _msgs = ({
	HIC"$N口中念了句咒文，朝$n一指，大喝一声：定！\n"NOR,
	HIR"结果$n手足僵硬，果然动弹不得！\n"NOR,
	HIR"结果$n被吓了一跳！\n"NOR
});

int cast(object me, object target)
{
	int dao = me->query_skill("dao", 1);	
	int cost = 50 + me->query("mana_factor");
	int ap, dp;

	target = BTL->get_victim(me, target);

	if(dao < 80) return notify_ok("你的道家仙法太低。\n");	
	if(!target)	return notify_fail("你想把谁定住？\n");
	if(target->is_busy()) return notify_fail(target->name() + "已经动弹不得了！\n");
	if(me->query("mana") < cost) return notify_fail("你的法力不足！\n");

	me->add("mana", -cost);

	ap = me->query("mana_factor") / 8;
	dp = target->query("mana_factor");

	message_vision(_msgs[0], me, target);

	if(random(ap + dp) > dp) {						//  1/9成功率
		message_vision(_msgs[1], me, target);
		target->start_busy(DURATION);
	} else {
		message_vision(_msgs[2], me, target);		
	} 
	me->start_busy(1);

	if(living(target)) target->kill_ob(me);
	return 3;
}

