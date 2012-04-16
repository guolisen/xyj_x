
#include <xyj_x.h>
#include <ansi.h>

inherit SSERVER;

#define	CD		8

#define MSG0	HIR"\n$N面带狞笑，露出白森森的牙齿往$n的鼻孔凑了过去，张嘴就是一吸！\n"NOR
#define MSG1	HIR"结果$n头皮一麻，只觉得体内阳气源源不断地流了出去！\n"NOR
#define MSG2	HIR "结果$n一扭头，避了开去！\n"NOR

int exert(object me, object target)
{
	int qi_gain, qi_lost, ap, dp, success, exp1, exp2;
	int skill = me->query_skill("tonsillit", 1);

	if(target == me) target = 0;
	target = BTL->get_victim(me, target);
	if(!target || !target->is_character() || target->is_corpse() || target == me)
		return notify_fail("你想摄取谁的阳气？\n");

	if(skill < 30) return notify_fail("你的摄气诀修为太低，不能摄取阳气。\n");

	if(me->query("family/family_name") != "阎罗地府" && !me->query_temp("is_zombie"))
		return notify_fail("你并非阎罗地府中人，不能摄取阳气。\n");

	if(me->query("kee") > me->query("max_kee") * 2)
		return notify_fail("你现在气太过充盈，再吸就要爆炸了。\n");

	qi_lost = target->query("kee") / 3;

	if(qi_lost < 5) return notify_fail("对方马上就要断气，没有什么好榨的了。\n");

	if(!cd_start(me, "im_pfm", CD)) return notify_ok("你现在还不能摄气。\n");

	message_vision(MSG0, me, target);

	success = 1;
	
	exp1 = me->query("combat_exp");
	exp2 = target->query("combat_exp");
	exp1 = pow(exp1 * 10, 0.333);
	exp2 = pow(exp2 * 10, 0.333);

	ap = me->query_skill("force") + exp1;
	dp = exp2;

	trace(exp1 + " " + exp2 + " " + ap);

	if(random(ap) + ap/2 < random(dp) + dp/2) success = 0;

	ap = me->query("max_mana");
	dp = target->query("max_mana");
	if(random(ap * 3) < dp) success = 0;

	if(success) {
		message_vision(MSG1, me, target);

		target->receive_damage("kee", qi_lost, me);
		me->add("kee", qi_lost);

		qi_gain = qi_lost / 2;
		if(exp2 < exp1) qi_gain = 0;
		trace("gain:" + qi_gain);
		me->improve_skill("tonsillit", 1 + qi_gain, skill > 200);
	} else {
		message_vision(MSG2, me, target);
	}
	if(success) COMBAT_D->report_status(target);
	if(living(target)) target->kill_ob(me);
	return 1;
}

