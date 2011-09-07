// by firefox 11/21/2009

inherit NPC;
inherit __DIR__"util";

#include <ansi.h>

void create()
{
	set_name(HIY"斑斓虎"NOR, ({"tiger", "hu"}));

	set("long",
"白额圆头，花身电目。四只蹄，挺直峥嵘；二十爪，钩弯锋利。\n"
"锯牙包口，尖耳连眉。狞狰壮若大猫形，猛烈雄如牛犊样。刚\n"
"须直直插银条，刺舌騂騂喷恶气。\n\n"
);

	set("race", "野兽");
	set("age", 10);
	set("per", 120);
	set("str", 120);

	set("max_kee", 1000);
	set("max_sen", 1000);

	set_skill("unarmed", 500);
	set_skill("dodge", 500);

	set("combat_exp", 500000);
	set("daoxing", 500000);

	set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
	set("verbs", ({ "bite", "claw" }) );
	set("chat_chance", 90);

	setup();
}



int leave()
{
	object me = this_object();
	message_vision("$N纵身急奔而去。\n"NOR, me);
	destruct(me);
	return 1;
}

void die()
{
	leave();
}

void unconcious()
{
	die();
}

int invocation(object leader)
{
	object me = this_object();

	copy_enemy(leader, me);
	me->set_temp("invoker", leader);
	me->set_leader(leader);
	me->move(environment(leader));
}

void heart_beat()
{
    object me = this_object();
	object leader = me->query_temp("invoker");

	::heart_beat();	//this_object可能在这里就挂了
	if(same_env(me, leader)) {
		if(leader->is_fighting() && !me->is_fighting()) copy_enemy(leader, me);
		else if(!me->is_fighting() && !random(60)) {
			string* cmds = ({"yawn", "lick " + getuid(leader), });
			me->command(random_1(cmds));
		}
	}
}