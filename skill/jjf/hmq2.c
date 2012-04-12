//by pkyou@DHXYII 2002/5/7
//大唐将军府霸王枪法之回马枪。

// 要点：败像（气血比），鲁莽（cor）,谨慎（cps）,经验?（exp）

inherit SSERVER;

#include <ansi.h>

#define CD					60

int perform(object me, object target)
{                             
	object weapon = me->query_temp("weapon");	
	object ridee = me->ride();
	int spear = me->query_skill("spear");
	int skill2 = spear + me->query_skill("dodge");
	string msg;
	int success = 0;

	if(me->query("family/family_name") != "将军府"  || me->query("betray/count"))
		return notify_ok("你是哪儿偷学来的武功，也想用回马枪?\n");

	if(!target) target = offensive_target(me);
	if(!target || !me->is_fighting(target) || !living(target))
		return notify_ok(HIW"你只能在战斗中使用。\n"NOR);

	if(!ridee)
		return notify_ok("回马枪需要坐骑配合。\n");

	if(me->query_temp("no_move") || ridee->query_temp("no_move"))	//破解『回马枪』
		return notify_ok("你动不了，没法诈败！\n");

	if(target->is_busy() || target->query_temp("no_move"))			//破解『回马枪』
		return notify_ok("对方暂时没空理你，别诈败了！\n");
	
	if(skill2 < 200)
		return notify_ok("你的枪法和身法都不济，还是省省吧！\n");

	if(me->query("force") < 500)
		return notify_ok("你内力不济，手脚发软，连枪都拿不稳。\n");

	if (target != me->query_temp("last_damage_from")) 
		return notify_ok("对方并未伤你，何苦下此狠手。\n");

	if(!cd_start(me, "hmq", CD))
		return notify_ok("诱敌之计不可滥用，否则没人会信了。\n");

	me->add("force", -300);

	msg = CYN"$N虚晃一枪回马便走，";

	{
		//败象：气血比
		int r1 = 100 * me->query("eff_kee") / (10 + me->query("max_kee"));
		int r2 = 100 * target->query("eff_kee") / (10 + target->query("max_kee"));

		//鲁莽程度
		int n1 = me->query("cor") - me->query("cps");
		int n2 = target->query("cor") - target->query("cps");

		//身法/枪法，来不及招架
		int d1 = skill2 / 2;						//枪法，身法
		int d2 = target->query_skill("dodge");		//身法

		if(d2 < 1) d2 = 1;

		trace("r1:" + r1 + "  r2:" + r2 + "  n1:" + n1 + "  n2:" + n2);

		success = r2 - r1 + (n2 - n1) + (d1 * 10 / d2);
		trace("success:" + success);

		success = success > random(100);
	}

	if(!success) {
		message_vision(msg + "$n唯恐有诈迟疑不决，未敢轻进。\n"NOR, me, target);
		call_out("remove_no_move", 1, target);	//不敢追，原地踏步
	} else {

		int damage = me->query_str() * me->query_temp("apply/damage") / 10;

		message_vision(msg + "$n紧追不舍。\n"NOR, me, target);
		message_vision(HIC"$n眼见要赶上$N，正欲出招，冷不防$N回身疾刺，直指咽喉！\n"NOR, me, target);

		trace("damage:" + damage);
		target->receive_damage("kee", damage, me);
		target->receive_wound("kee", damage, me);

		COMBAT_D->report_status(target);

		me->start_busy(1);
		target->start_busy(1);		//吓坏了
	}
	return 1;
}

void remove_no_move(object who)
{
	if(who) who->delete_temp("no_move");
}
