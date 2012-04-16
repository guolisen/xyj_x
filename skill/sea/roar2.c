#include <ansi.h>

inherit F_CLEAN_UP;
#include "/cmds/std/valid_kill.h"


int exert(object me, object target)
{
	object env = environment(me);
	int skill = me->query_skill("force");
	int force = me->query("max_force");
	int cost = skill / 5;
	int damage = 0;

	if(env->query("no_fight")) return notify_fail("安全区内不能乱吼乱叫！\n");

	if(me->query("force") < cost ) return notify_fail("你的内力不够。\n");

	me->add("force", -cost);
	me->start_busy(5);
	message_vision(HIR "\n$N退后两步，深深地吸一口气，猛然发出股如山崩海啸般的龙吟！\n\n"NOR, me);
	
	foreach(object ob in all_inventory(env)) {
		if(!living(ob) || ob == me) continue;
		if(!me->visible(ob) && wizardp(ob)) continue;
		if(!valid_kill(me, ob ,0)) continue; // mon 6/28/99

		damage = skill + force/10 - ob->query("max_force") / 10;
		if( damage > 0 ) {
			ob->receive_damage("sen", damage, me);
			if(ob->query("force") < skill * 2 )
				ob->receive_wound("sen", damage/2, me);
			tell_object(ob, "你觉得眼前一阵金星乱冒，耳朵痛得像是要裂开一样！\n");
		}
		COMBAT_D->report_sen_status(ob);
		if(userp(ob)) ob->fight_ob(me);
		else if(!ob->is_killing(me)) ob->kill_ob(me);
	}

	return 1;
}

