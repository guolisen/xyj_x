// animate.c

inherit F_CLEAN_UP;

#include <ansi.h>

#define CD			15
//判断是否在夜间
#define at_night() (NATURE_D->query_current_day_phase() / 6)

object animate(object who, object target);

int cast(object me, object target)
{
	object zombie;
	int skill = me->query_skill("gouhunshu", 1);

	if( !me->is_fighting() ) return notify_fail("你只有在战斗中才能使用复活术。\n");
	if( me->query("mana") < 200 ) return notify_fail("你的法力不够！\n");
	if(!cd_start(me, "invoke", CD)) return notify_ok("你暂时不能驱动僵尸！\n");

	if(target && !target->is_corpse()) target = 0;

	if(!target && !at_night()) return notify_fail("你要驱动哪一具尸体？\n");

	
	me->add("mana", -50);

	zombie = animate(me, target);
	
	if(target) {
		message_vision(CYN"$N对著地上的$n喃喃地念了几句咒语，$n抽搐了几下竟站了起来！\n"NOR, me, target);
		destruct(target);
	}
	else
		message_vision(CYN"$N喃喃地念了几句咒语，地下伸出一只干枯的手，接着$n挣扎着爬了出来！\n"NOR, me, zombie);

	zombie->animate(me);
	zombie->reset_action();
	zombie->add_temp("apply/attack", skill / 4);

	call_out("dest_zombie", 60, zombie);
	return 5;	//3+random(5);
}

void dest_zombie(object zombie)
{
	if(zombie) zombie->die();
}

object animate(object who, object target)
{
	object zombie;
	string name = target ? target->query("victim_name") : "无名";

	seteuid(getuid());
	zombie = new("/obj/npc/zombie");
	zombie->set_name( name + "的僵尸", ({ "zombie" }) );
	zombie->move(environment(who));
	zombie->set_temp("invoker", who);
	return zombie;
}