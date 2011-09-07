// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit NPC;
inherit F_GREET;

#define same_camp			ALX->camp_same
#define EVENTS				"bg/events"


//设置事件响应
void set_events(mapping events)
{
	set(EVENTS, events);
}

void setup()
{
	set("str", 20);
	set("cor", 10);
	set("int", 40);
	set("spi", 40);
	set("cps", 40);
	set("per", 20);
	set("con", 40);
	set("kar", 40);

	set_temp("apply/defense", 100);
	set_temp("apply/armor", 300);

	set_heart_beat(6);

	::setup();
}

void init()
{
	object me = this_object();
	object who = this_player();
	mapping events = query(EVENTS);

	::init();

	if(!same_camp(me, who)) {
		greet(me, who, events["init"]);
	}

}

int prevent_learn(object me, string skill)
{
	command("say 当前战事正紧，来日再说。");
	return 1;
}

private void recover_status(object me)
{
	int n = 500;

	HP->add_mana(me, n);
	HP->add_force(me, n);
	me->receive_curing("kee", n * 2);
	me->receive_heal("kee", n * 2);
	me->receive_curing("sen", n * 2);
	me->receive_heal("sen", n * 2);
}

private int is_half()
{
	object me = this_object();
	return me->query("eff_kee") < me->query("max_kee") / 2
		|| me->query("eff_sen") < me->query("max_sen") / 2;
}

private void cmd(object me, mixed cmds_fun)
{
	if(arrayp(cmds_fun)) me->command(random1(cmds_fun));
	if(functionp(cmds_fun)) evaluate(cmds_fun, me);
}

void heart_beat()
{
    object me = this_object();
	object leader = me->query_temp("invoker");
	mapping events = query(EVENTS);

	::heart_beat();	//this_object可能在这里就挂了
	if(!same_env(me, leader)) return;

	if(leader->is_fighting()) BTL->copy_enemy(leader, me);
	
	if(me->is_fighting()) cmd(me, events["cmds"]);
	else recover_status(me);
		
}

int leave()
{
	object me = this_object();
	string msg = me->query(EVENTS"/leave");

	if(msg) msv(msg + "\n"NOR, me);
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

int invocation(object leader, int duration)
{
	object me = this_object();
	mapping events = query(EVENTS);

	BTL->copy_enemy(leader, me);
	me->set_temp("invoker", leader);
	me->set_leader(leader);
	me->move(environment(leader));

	if(events["born"]) msv(events["born"] + NOR"\n", me);

	BUFF->start_life(me, duration, events["leave"]);
}
