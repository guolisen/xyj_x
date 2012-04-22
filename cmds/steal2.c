
#include <xyj_x.h>
#include <ansi.h>
#include "/cmds/std/valid_kill.h"

inherit F_CLEAN_UP;

#define CD		1
#define THR		100

int main(object me, string arg)
{
	object env = environment(me);
	string what, who;
	object ob, victim;
	
	if(env->query("no_fight")) return notify_fail("这里禁止行窃。\n");
	if(!arg || sscanf(arg, "%s from %s", what, who) != 2)
		return notify_fail("指令格式：steal <物品> from <人物>\n");
	
	victim = present(who, env);

	if(!victim || victim == me) return notify_fail("你想行窃的对象不在这里。\n");
	if(!valid_kill(me, victim, 0)) return 0;
	if(!wizardp(me) && wizardp(victim)) return notify_fail("玩家不能偷巫师身上的东西。\n");

	if(!ob = present(what, victim)) {
		object* inv = all_inventory(victim);
		if(!sizeof(inv)) return notify_fail( "对方身上看起来没有什么东西好偷。\n");
		ob = inv[random(sizeof(inv))];
	}
	if(!cd_start(me, "steal", CD)) return notify_fail("连续出手危险性太高了。\n");

	write("你不动声色地慢慢靠近" + victim->name() + "，等待机会下手 ...\n\n");
	call_out("complete_steal", 3, me, victim, ob);
	return 1;
}

private void complete_steal(object me, object victim, object ob)
{
	if(!me || !living(me)) return;
	else if(!me->close_to(victim)) tell_object(me, "太可惜了，你下手的目标已经走了。\n");
	else if(!ob || ob->query("no_give") || ob->query("no_get")) tell_object(me, "你伸手摸了个空。\n");
	else if(me->is_busy()) tell_object(me, "你自顾不暇没机会下手。\n");	
	else {		
		int ratio = 1000;
		if(living(victim)) {
			mapping cmps = ([
				"prop"		: ([ CEXP : 1, "spi" : 2, "per" : 1, "str" : -1, "sen" : 1, "max_sen" : -1 ]),
				"skill"		: ([ "stealing" : 3, "dodge" : 2 ]),
				"temp"		: ([ "no_move" : -1 ]),
			]);
			ratio = BTL->cmp_random20(me, victim, cmps);
			if(me->is_fighting()) { me->start_busy(3); ratio -= 10; }
			if(!cd_end(me, "thief")) ratio -= 10;
			if(!cd_end(victim, "stolen")) ratio -= 40;
			if(victim->is_fighting()) ratio -= 10;
			if(victim->is_busy()) ratio += 10;
			if(ob->query("equipped")) ratio -= 80;
		}
		trace("steal:" + ratio);
		if(ratio > THR) {
			if(!ob->move(me)) {
				tell_object(me, "你摸到" + ob->unit_name() + "，可太重了，不得不放弃。\n");
				return;
			}
			if(random(ratio) * 4 < THR)
				message_vision(CYN"$N不小心和$n撞了个满怀，匆匆跑开。\n"NOR, me, victim);

			tell_object(me, HIW "得手了！\n\n" NOR);
			tell_object(me, "你偷到" + ob->unit_name() + "！\n");
			if(ratio < THR + 20) me->improve_skill("stealing", 1 + random(me->query("int")));
		} 
		else if(random(ratio) * 2 > THR) {
			tell_object(me, victim->name() + "不经意地一转头，你急忙将手缩了回去！\n还好，没有被发现。\n");
		} else {
			tell_object(me, HIR"糟糕！你失手了！\n\n"NOR);
			message_vision("$N一回头，正好发现$n的手正抓着$P身上的" + ob->name() + "！\n\n"
				+ "$N喝道：「干什么！」\n\n", victim, me);
			if(userp(victim)) victim->fight_ob(me);
			else victim->kill_ob(me);
			me->fight_ob(victim);
			me->start_busy(5);
			me->add("thief", 1);
			cd_start(me, "thief", CD * 5);				//现行后被大众防备
			cd_start(victim, "stolen", CD * 10);		//被盗后警觉
		}
	}
}

int help(object me)
{
write(@HELP
指令格式 : steal <某物> from <某人>

这个指令让你有机会偷到他人身上的东西。成功了, 当然你就能获得
该样物品。可是, 马有失蹄, 人总有失风的时候, 当你失败时当然就
得付出代价, 至于是什么代价......靠你自己去发掘罗。
HELP
    );
    return 1;
}
