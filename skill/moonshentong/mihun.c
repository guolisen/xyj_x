// mihun.c 迷魂术
#include <ansi.h>

inherit SSERVER;

#define DURATION			30

void free(object target);

int cast(object me, object target)
{
	string msg;
	int success, ap, dp;

	if( !target ) target = offensive_target(me);

	if(me->query_skill("moonshentong",1) < 60)
		return notify_fail("你还没学会迷魂术。。。\n");

	if( !target
		||      !target->is_character()
		||      target->is_corpse()
		||      target==me)
		return notify_fail("你想迷谁的魂？\n");  

	if(target->query_temp("no_move"))
		return notify_fail(target->name() + "已经魂不守舍，呆若木鸡了！\n");  

	if((int)me->query("mana") < 200 )
		return notify_fail("你的法力不够！\n");

	me->add("mana", -200);


	msg = HIC"$N低头轻声念了句咒文，又抬起头来朝$n妩媚地一笑！\n"NOR;

	success = 1;

	ap = me->query_skill("spells") / 10;
	ap = ap * ap * ap / 12 ;

	ap += me->query("daoxing") / 1000;
	dp = target->query("daoxing") / 1000;

	ap += me->query_per() * 5000 / 1000;
	dp += target->query_per() * 5000 / 1000;

	ap += me->query("mana") * 200 / 1000;
	dp += target->query("mana") * 200 / 1000;
	
	if(random(ap+dp) < dp) success = 0;

	//here we compare current mana. this is important. you need recover to try again.

	if(success == 1 ){
		msg +=  HIR "$n神不守舍地看着$N，怜香惜玉之心由然而起，竟然忘了自己在战斗之中。\n" NOR;
		target->set_temp("no_move", 1);

		call_out("free", DURATION, target);
	}	    
	else {
		msg +=  HIR "$n鄙夷地看了$N一眼，毫不为所动！\n" NOR;	
		me->start_busy(1);
		if( living(target) ) target->kill_ob(me);
	} 

	message_vision(msg, me, target);

	return 3 + 2;
}

void free(object target)
{
	if (target)
		target->delete_temp("no_move");      
	return;
}

