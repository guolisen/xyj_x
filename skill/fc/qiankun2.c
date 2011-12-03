// firefox 2011.12
#include <ansi.h>
#include <xyj_x.h>

#define RESERVE_FORCE			5
#define EFF_DURATION			8

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

///检查特效的触发
void check_eff(object me, object target)
{
	int ap = me->query_str();
	int dp = target->query_str();

	if(me->query_temp("last_damage_from") == target) ap += ap / 3;	//受伤而愤怒

	if(random(ap) > dp) {
		message_vision(HIC"\n$n被$N硬生生钉入地下动弹不得！\n"NOR, me, target);
		BTL->start_no_move(target, EFF_DURATION);
	}
}

int perform(object me, object target)
{
	int enhance = me->query_skill("wuxiangforce", 1) / 3;

	object weapon = me->query_temp("weapon");
	int skill = me->query_skill("qianjun-bang", 1);	
	int cost = 100 + me->query("force_factor");

	target = BTL->get_victim(me, target);

	if(!target || !me->is_fighting(target))	return notify_fail("「乾坤一棒」只能在战斗中使用！\n");
	if(skill < 120)	return notify_fail("你的千钧棒级别还不够！\n");
	if(me->query("force") < cost) return notify_fail("你的内力不足！\n");
	if(!cd_start(me, "im_pfm", 2)) return notify_fail("绝招用的太多太滥就不灵了。\n");

	me->add("force", -cost);

	message_vision(HIC"\n$N运足精神，一个高跳在空，使出了「乾坤一棒」的绝技！\n"NOR,me);

	if(!BTL->loyal_member(me, "方寸山三星洞")) enhance = 0;
	if(!cd_start(me, "reserve_force", RESERVE_FORCE)) enhance = 0;

	me->add_temp("apply/strength", enhance);
	me->set("actions", _action);
	if(COMBAT_D->do_attack(me, target, weapon) > 0 && enhance > 0) check_eff(me, target);
	me->reset_action();
	me->add_temp("apply/strength", -enhance);
		
	BTL->fight_enemy(target, me);

	BTL->start_no_move(me, 1);
	return 1;
}
