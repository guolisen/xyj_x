// zouxiao.c  碧箫传情  

#include <xyj_x.h>

#include <ansi.h>
inherit SSERVER;

#define CD				8

int perform(object me, object target)
{
	object weapon = me->query_temp("weapon");    
	
	int cost = me->query_skill("spells") / 2;
	int damage, ap, dp, ratio;

	if( !target ) target = offensive_target(me);

	if( !target
		||      !target->is_character()
		||      target->is_corpse()
		||      target==me)
		return notify_fail("你要对谁奏箫？\n");

	if (!weapon || weapon->query("music/type") != "xiao")
		return notify_fail("你手里的家伙吹不出调子。\n");

	if (me->query_skill_mapped("force")!="zhenyuan-force")
		return notify_fail("只有用镇元神功才能运力吹箫。\n");

	if (me->query_skill("xiaofeng-sword",1)<50)
		return notify_fail("你的晓风残月剑还得再练练。\n");

	if (me->query_skill("zouxiao",1)<60)
		return notify_fail("你奏箫的功夫还不够，再好好练练吧。\n");

	if (target->query_skill("literate",1)<50)
		return notify_fail("对他吹箫？还不如对牛弹琴呢。\n");

	if(me->query("force") < 500 )
		return notify_fail("你的内力还不到火候。\n");

	if(!cd_start(me, "im_pfm", CD))
		return notify_fail("绝招总用就不灵了！\n");

	me->add("force", -cost);

	ap = (me->query_skill("xiaofeng-sword", 1)
		+ me->query_skill("zouxiao", 1)
		+ me->query_skill("literate")) / 2;
	
	dp = (target->query_skill("literate")
		+ target->query_skill("spells")) / 2;

	damage = ap * 2;

	ap += pow(me->query("daoxing") * 1, 0.333);
	dp += pow(target->query("daoxing") * 1, 0.333);

	dp = dp > 1 ? dp : 1;
	ratio = ap * 100 / dp;
	trace(sprintf("%s ap=%d dp=%d ratio=%d damage=%d", getuid(me), ap, dp, ratio, damage));
	ratio += random(41) - 20;

	message_vision(HIM"$N对着$n奏起了一曲，箫声凄凉，如是一滴滴小雨落上树叶。\n"NOR, me, target);

	if(ratio < 90) {
		message_vision(YEL"可$n冲耳不闻，不为所动。\n"NOR, me, target);
	} else {	
		message_vision(HIG"$n听了箫声，心中莫名其妙的感到一阵酸楚，悲从中来，泪水正涔涔落下。\n"NOR, me, target);
		target->receive_damage("sen", damage, me);
		target->receive_wound("sen", damage / 4, me);
		COMBAT_D->report_sen_status(target);
	}
	target->kill_ob(me);

	return 1;
}

