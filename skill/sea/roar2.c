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

	if(env->query("no_fight")) return notify_fail("��ȫ���ڲ����Һ��ҽУ�\n");

	if(me->query("force") < cost ) return notify_fail("�������������\n");

	me->add("force", -cost);
	me->start_busy(5);
	message_vision(HIR "\n$N�˺��������������һ��������Ȼ��������ɽ����Х���������\n\n"NOR, me);
	
	foreach(object ob in all_inventory(env)) {
		if(!living(ob) || ob == me) continue;
		if(!me->visible(ob) && wizardp(ob)) continue;
		if(!valid_kill(me, ob ,0)) continue; // mon 6/28/99

		damage = skill + force/10 - ob->query("max_force") / 10;
		if( damage > 0 ) {
			ob->receive_damage("sen", damage, me);
			if(ob->query("force") < skill * 2 )
				ob->receive_wound("sen", damage/2, me);
			tell_object(ob, "�������ǰһ�������ð������ʹ������Ҫ�ѿ�һ����\n");
		}
		COMBAT_D->report_sen_status(ob);
		if(userp(ob)) ob->fight_ob(me);
		else if(!ob->is_killing(me)) ob->kill_ob(me);
	}

	return 1;
}

