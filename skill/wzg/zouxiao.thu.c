// cracked by vikee 2/09/2002   vikee@263.net
// zouxiao.c  碧箫传情  

#include <ansi.h>
inherit SSERVER;

#define PFM_ID		"zouxiao"
#define PFM_DELAY	6

string* skills = ({"zouxiao", "qin", "literate"});

//计算skill平均值
int avg_skill(object who, string* list)
{
	int n = sizeof(list);
	int sum = 0;
	foreach(string skill in list) {
		sum += who->query_skill(skill, 1);
	}
	return n ? sum / n : 0;
}

int perform(object me, object target)
{
	string msg;
	int damage, ap, dp,qixue,eff_qi,max_qi,qi_pcg;
	object weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);

	if( !target
		||      !target->is_character()
		||      target->is_corpse()
		||      target==me)
		return notify_fail("你要对谁奏箫？\n");

	if (me->query_temp(PFM_ID"_busy")>time()) return notify_fail("绝招用的太多太滥就不灵了。\n");

	if( !me->is_fighting(target) || target->is_busy() )
		return notify_fail("大家都很忙，没人有时间听你吹吹打打。\n");

	if (!weapon || weapon->query("music/type") != "xiao")
		return notify_fail("你手里的家伙吹不出调子。\n");

	if (me->query_skill_mapped("force")!="zhenyuan-force")
		return notify_fail("只有用镇元神功才能运力吹箫。\n");

	if (me->query_skill("xiaofeng-sword",1)<50)
		return notify_fail("你的晓风残月剑还得再练练。\n");

	if (me->query_skill("zouxiao",1)<60)
		return notify_fail("你奏箫的功夫还不够，再好好练练吧。\n");

	if((int)me->query("force") < 200 )
		return notify_fail("你的内力还不到火候。\n");

	if((int)me->query("kee") < 200 )
		return notify_fail("你的体力已经不够了！\n");

	if((int)me->query("sen") < 200 )
		return notify_fail("你无法集中精力！\n");

	msg = HIC "\n$N举起"+weapon->query("name")+HIW"，对着$n奏起了一曲，箫声凄凉，"
		+"似是叹息，又似哭泣，跟着\n箫声颤抖，发出瑟瑟瑟断续之音，如是一滴滴小雨落上树叶。\n" NOR,

	me->add("sen", -150);
	me->add("kee", -150);
	me->add("force", -150);

	ap = 2 * avg_skill(me, ({"xiaofeng-sword"}) + skills);
	damage = ap * ap / 300;
	ap = ap * 3 + pow((int)me->query("combat_exp"), 0.333);
	
	dp = 2 * avg_skill(target, ({"spells"}) + skills);
	dp = dp * 3 + pow((int)target->query("combat_exp"), 0.333);

	if( random(100*ap/dp) <  5 ) 
	{
		msg += HIW "$n冲着你鄙意的冷笑道：就这点本事，也来贻笑大方？"
			+"$N顿时羞愧难当。\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(2);	//失败代价太大是很多技能废掉的原因
	} 
	else if( random(100*ap/dp) <  50 ) 
	{
		msg += HIW "可$n冲耳不闻，不为所动。\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(1);
	}
	else 
	{
		DAMAGE_D->bring_damage(target, "sen", damage, "magic", "spells", me);
		//target->receive_damage("sen",damage,me);
		msg += HIW "$n听了箫声，心中莫名其妙的感到一阵酸楚，悲从中来，泪水正涔涔落下。\n"NOR;
		message_vision(msg, me, target);
		COMBAT_D->report_sen_status(target);
		target->start_busy(3);
		me->start_busy(1);
		if(!random(3)) me->improve_skill("zouxiao", 1);
	}
	target->kill_ob(me);
	
	me->set_temp(PFM_ID"_busy", time() + PFM_DELAY );
	return 1;
}
