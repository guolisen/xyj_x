// firefox 2011.12

#include <ansi.h>
#include <xyj_x.h>

#define CD			5
#define NAME		HIW"霹雳三打"NOR

int perform(object me, object target)
{
	object weapon = me->query_temp("weapon");
	int skill = me->query_skill("qianjun-bang", 1);	
	int cost = 50 + me->query("force_factor");

	target = BTL->get_victim(me, target);

	if(!target || !me->is_fighting(target))	return notify_fail("「"NAME"」只能在战斗中使用！\n");
	if(skill < 60)	return notify_fail("你的千钧棒级别还不够！\n");
	if(me->query("force") < cost) return notify_fail("你的内力不足！\n");
	if(!cd_start(me, "im_pfm", CD)) return notify_fail("你暂时还不能使用"NAME"。\n");

	me->add("force", -cost);

	message_vision(HIC"\n$N运足精神，身形一转，霹雳间连续向$n攻出了三招！\n"NOR, me, target);

	me->set_temp("QJB_perform", 4);
	COMBAT_D->do_attack(me, target, weapon);
	me->set_temp("QJB_perform", 1);
	COMBAT_D->do_attack(me, target, weapon); 
	me->set_temp("QJB_perform", 6);
	COMBAT_D->do_attack(me, target, weapon);
	me->delete_temp("QJB_perform");

	BTL->fight_enemy(target, me);
	BTL->start_no_move(me, 3);

	return 1;
}
