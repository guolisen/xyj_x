
//六道轮回

#include <ansi.h>

inherit F_DBASE;
inherit SSERVER;

void delay_effect(object me, object target, object weapon,int power);

int perform(object me, object target)
{
	int delay,skill;
	object weapon=me->query_temp("weapon");
	
	if( !target ) target = offensive_target(me);
	if (!target) return notify_fail("打谁？\n");
	if (!me->is_fighting(target))
		return notify_fail("你们不在打架。\n");
	skill=me->query_skill("tonsillit",1);        
	if (skill<60) return notify_fail("你的摄气诀不够纯熟。\n");
	skill=me->query_skill("whip");
	if (skill<100) 
		return notify_fail("你的鞭法太差劲了。\n"); 
	if( (int)me->query("force") < 300 )      
		return notify_fail("你的内力不够。\n");
	if( (int)me->query_temp("lunhui_delay") )
		return notify_fail("你已经在施展六道轮回了。\n");

	me->add("force", -200);
	delay=4;//random(4)+1;
	message_vision(HIB"$N阴恻恻地一笑，手中"+weapon->name()+
		HIB"突然慢了下来，$n一见大喜，抓住机会，上前就是一轮疾攻！\n"NOR, me,target);
	//        tell_object(me,delay+"\n");
	me->set_temp("lunhui_delay", 1);
	me->start_busy(delay);
	
	call_out("delay_effect", delay * 2, me, target, weapon, delay);

	return 1;
}


mapping _action = ([
	"action"		: "$N大喝一声，手中$w宛若矫龙飞在半空，大有「横空出世」的气概。\n$n只觉得全身俱在$w笼罩之下",
	"damage"		: 50,
	"force"			: 50,
	"dodge"			: -20,
	"parry"			: -20,
	"damage_type"	: "抽伤",
]);

void delay_effect(object me, object target, object weapon, int power)
{
	int attack,damage;
	object env;

	if(!me) return;
	me->delete_temp("lunhui_delay");
	env = environment(me);
	
	if(!target || env != environment(target) || env->query("no_fight")) return;		// 2010.11 for 擂台下打死人
	if(!weapon || me->query_temp("weapon") != weapon) return;	

	message_vision(HIR"$N鞭势突然一变，手中"+weapon->name()
		+ HIR"幻做漫天鞭影，将$n的退路全部封死。\n"NOR,me,target);
	message_vision(HIR"$N觉得有如置身炼狱，四周都是熊熊鬼火，深受轮回之苦，连气都透不过来。\n"NOR,target);
	
	attack = me->query_skill("hellfire-whip") * power;
	damage = power * me->query_temp("apply/damage") + me->query("force_factor");

	target->add_temp("apply/defense", -attack);								// 2010.11 for 防止溢出
	me->add_temp("apply/damage", damage);
	
	me->set("actions", _action);
	COMBAT_D->do_attack(me, target, weapon);
	me->reset_action();

	me->add_temp("apply/damage", -damage);									// 2010.11 for damage bug
	target->add_temp("apply/defense", attack);	
}

