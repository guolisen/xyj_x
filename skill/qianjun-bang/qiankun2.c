#include <ansi.h>

inherit SSERVER;


mapping _action = ([
	"name"		: "乾坤一棒",
	"action"	:
		"$N将手中$w迎风一挥，幻出万千虚影，蓄力劲发，高举过顶，\n"
		"$w对准$n的脑门就砸了下去。这一下要是打中，恐怕连大罗金仙也难逃一命",
	"parry"		: -50,
	"dodge"		: -50,
	"damage"	: 200,
	"damage_type":  "砸伤"
]);

int perform(object me, object target)
{
	int damage = me->query_skill("wuxiangforce", 1) / 5;

	if(!target) target = offensive_target(me);

	if(!target || !me->is_fighting(target))
		return notify_fail("「乾坤一棒」只能在战斗中使用！\n");

	if(me->query("force") < 1000 )
		return notify_fail("你的内力不足！\n");

	if(me->query_skill("qianjun-bang", 1) + me->query_kar() < 150)
		return notify_fail("你的千钧棒级别还不够，使用这一招会有困难！\n");

	if(!cd_start(me, "im_pfm", 2))
		return notify_fail("绝招用的太多太滥就不灵了。\n");

	me->add("force", -200);

	message_vision(HIC"\n$N运足精神，一个高跳在空，使出了「乾坤一棒」的绝技！\n"NOR,me);

	if(!userp(me) || me->query("betray/count")) damage = 0;
	me->add_temp("apply/damage", damage);
	trace("damage:" + damage);
	me->set("actions", _action);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	me->reset_action();

	me->add_temp("apply/damage", -damage);
		
	if(!target->is_fighting(me)) {
		if( living(target) ) {
			if( userp(target) ) target->fight_ob(me);
			else target->kill_ob(me);
		}
	}

	me->set_temp("no_move", 1);
	call_out("remove_no_move", 1, me);
	return 1;
}

void remove_no_move(object me) {
	if (me) me->delete_temp("no_move");
}
