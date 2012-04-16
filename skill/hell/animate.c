// animate.c

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>


#define CD			15
#define DURATION	60


object animate(object who, object target);

int cast(object me, object target)
{
	object zombie;
	int skill = me->query_skill("gouhunshu", 1);

	if( me->query("mana") < skill ) return notify_fail("你的法力不够！\n");
	if(!cd_start(me, "invoke", CD)) return notify_ok("你暂时不能驱动僵尸！\n");
	
	me->add("mana", -skill);

	zombie = animate(me, target);
	zombie->add_temp("apply/attack", skill / 4);
	zombie->set_temp("is_zombie", 1);

	zombie->set("chat_chance_combat", 30);
	zombie->set("chat_msg_combat", ({ (: call_other, zombie, "exert_function", "sheqi" :), }));	
	zombie->set("long",	"这是一具被人用符咒控制的僵尸，从它苍白的脸上看不出任何喜怒哀乐。\n");
	zombie->set("cps", 10000);
	zombie->set("per", 10);

	zombie->set_life(DURATION, "$N慢慢地倒了下去，化为一滩血水。\n");
	return 5;
}

object animate(object who, object target)
{
	object zombie = GUARD->new_hufa(who);
	string name;

	if(target) {
		name = target->query("victim_name")  + "的僵尸";
		message_vision(CYN"$N对著地上的$n喃喃地念了几句咒语，$n抽搐了几下竟站了起来！\n"NOR, who, target);
		destruct(target);
	} else {
		name = "无名僵尸";
		message_vision(CYN"$N喃喃地念了几句咒语，地下伸出一只干枯的手，接着" + name + "挣扎着爬了出来！\n"NOR, who);
	}
	zombie->set_name(name, ({ "zombie" }));
	return zombie;
}