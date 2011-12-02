#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
	object weapon;

	int skill = me->query_skill("qianjun-bang", 1);	
	int cost = 50 + me->query("force_factor");
	int ap, dp;

	target = BTL->get_victim(me, target);

	if(!target)	return notify_fail("你要对谁施展「霹雳三打」？\n");
	if(!me->is_fighting()) return notify_fail("「霹雳三打」只能在战斗中使用！\n");
	if(me->query("force") < cost) return notify_fail("你的内力不足！\n");
	if(skill < 100)	return notify_fail("你的千钧棒级别还不够！\n");
	if(!cd_start(me, "im_pfm", 6)) return notify_fail("绝招用的太多太滥就不灵了。\n");

	me->add("force", -cost);

	message_vision(HIC"\n$N运足精神，身形一转，霹雳间连续向$n攻出了三招！\n"NOR, me, target);

	me->set_temp("QJB_perform", 4);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	me->set_temp("QJB_perform", 1);  
	COMBAT_D->do_attack(me, target, me->query_temp("weapon")); 

	me->set_temp("QJB_perform", 6);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	me->delete_temp("QJB_perform");

	BTL->fight_enemy(target, me);

	if(!me->query_temp("no_move")) {
		me->set_temp("no_move", 1);
		call_out("remove_no_move", 3, me);
	}

	return 1;
}

void remove_no_move(object me) 
{
	if(me) me->delete_temp("no_move");
}
