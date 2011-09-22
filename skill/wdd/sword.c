
inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>
#include <combat.h>

#define CD				15
#define BUFF_ID			"bleeding"
#define BUFF_NAME		"流血"

#define YS_ID			"yinshen2"

int on_timer(mapping buff);

int perform(object me, object target)
{
	object weapon = me->query_temp("weapon");
	int cost = 200;
	int ap, dp;
	string msg;

	if(!target) target = offensive_target(me);

	if(!target || !target->is_character() || target->is_corpse() || target == me)
		return notify_fail("你要攻击谁？\n");
	
	if(!target->is_fighting(me))
		return notify_fail("你们没有在打架！\n");
	
	if(me->query("force") < cost)
		return notify_fail("你内力不继，难以出招。\n");

	
	if(!cd_start(me, "im_pfm", CD))
		return notify_fail("绝招用的太多太滥就不灵了。\n");

	me->add("force", -cost);

	message_vision(HIB"突然间阴风从地起，残影荡微光；$N手中铁白耀星芒，直逼$n！\n"NOR, me, target);
	msg = CYN"$N赶忙躲闪招架，如玉楼抓翡翠，金殿碎鸳鸯。剑光止处，";

	ap = COMBAT_D->skill_power(me, "sword", SKILL_USAGE_ATTACK);
	dp = COMBAT_D->skill_power(target, "dodge", SKILL_USAGE_DEFENSE);
	dp += COMBAT_D->skill_power(target, "parry", SKILL_USAGE_DEFENSE);

	dp /= 2;

	if(target->query_temp("no_move")) dp /= 2;
	if(target->is_busy()) dp /= 3;
	
	trace("ap:" + ap + " dp:" + dp);
	
	if(ap > dp + random(dp * 2)) {	//基础命中25%，一般情况下命中0%
		
		int heal = me->query_skill_mapped("spells") == "yaofa";
		int power = 1 + me->query_skill("huntian-qigong", 1) / 20;
		int damage = power * me->query_temp("apply/damage");
		mapping buff = BUFF->find(target, BUFF_ID);

		trace("total damage:" + damage);

		if(buff) {
			buff["_damage"] += damage;
		} else {
			buff = ([
				"id"		: BUFF_ID,
				"name"		: BUFF_NAME,
				"comment"	: "身上血流不止。",
				"interval"	: 2,
				"timer_act"	: (: on_timer :),
				"_damage"	: damage,
				"_heal"		: heal,
				"_attacker"	: me,
			]);
			BUFF->add(target, buff);
		}
		message_vision(msg + "血流如注。\n"NOR, target);
	} else {
		message_vision(msg + "毫发无损。\n"NOR, target);
	}

	return 1;
}

//目标处于安全区
int in_safy(object who)
{
	object env = environment(who);
	return env && (env->query("no_fight") || env->query("no_magic"));
}

int on_timer(mapping buff)
{
	object me = buff["me"];
	int damage = buff["_damage"] / 3;
	object attacker = buff["_attacker"];
	mapping ys_buff = BUFF->find(me, YS_ID);

	if(in_safy(me) || damage < 10) return 0;

	me->add("force", -damage*5);		//力气也会随着血流干
	
	me->receive_damage("kee", damage);
	me->receive_wound("kee", damage, attacker);
	
	if(buff["_heal"] && attacker && attacker->is_fighting(me))
		attacker->receive_curing("sen", damage);	//见血就兴奋

	message_vision(RED"$N身上的血静静的滴落。\n"NOR, me);
	buff["_damage"] -= damage;

	if(random(2) && damage > 500 && ys_buff)		//血流过多会破除隐身
		BUFF->remove1(ys_buff);

	return 1;
}
