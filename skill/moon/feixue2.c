//added by huadao .2010.07.24
#include <ansi.h>

inherit SSERVER;

#define CD			1

mapping* _acts = ({
	([
		"action"		: "$N向上轻轻跃起，风回雪舞剑如暴雨梨花，向$n迎面打来"NOR,
		"damage"		: 300,
		"damage_type"	: "刺伤",
	]),
	([
		"action"		: "$N身体斜斜向上飘出，也不回头，反手就刺出了一招",
		"damage"		: 300,
		"damage_type"	: "刺伤",
	]),
	([
		"action"		: "$N一声怒叱，长剑幻作千百支冰箭，犹如漫天飞雪扑向$n",
		"damage"		: 300,
		"damage_type"	: "刺伤",
	])
});

int perform(object me, object target)
{
	object weapon = me->query_temp("weapon");
	int skill = me->query_skill("snowsword", 1);

	if(!target) target = offensive_target(me);

	if(!target
		||      !target->is_character()
		||      target->is_corpse()
		||      target == me)
		return notify_fail("你要对谁施展「漫天飞雪」？\n");

	if(me->query("force") < 400)
		return notify_fail("你的真气不够！\n");

	if(!me->is_fighting())
		return notify_fail("「漫天飞雪」只能在战斗中使用！\n");

	if( skill < 50)
		return notify_fail("你的风回雪舞剑法级别还不够，使用这一招会有困难！\n");

	if(me->query("betray/count"))
		return notify_fail("[漫天飞雪]是月宫不传之密！\n");

	if( me->query("force_factor") > 0)
		return notify_fail("「漫天飞雪」绝技重招不重力。加力出招怎能剑走轻灵？\n");

	if(!cd_start(me, "feixue", CD)) 
		return notify_fail("绝招用多就不灵了！\n");

	me->add("force", -200);
	
	message_vision(HIW"\n$N轻叱一声，身体急速上旋，接着剑光闪动幻作漫天飞雪卷向$n。\n"NOR, me, target);

	if(userp(target)) skill *= -1;
	
	me->add_temp("apply/attack", skill);

	foreach(mapping act in _acts) {
		me->set("actions", act);
		COMBAT_D->do_attack(me, target, weapon);
	}
	me->reset_action();

	me->add_temp("apply/attack", -skill);

	if(!target->is_fighting(me) && living(target)) {
		if( userp(target) ) target->fight_ob(me);
		else target->kill_ob(me);
	}

	return 1;
}


