
#include "alx.h"


//复活
private int revive_act(mapping buff)
{
	object me = buff["me"];
	object* forts = ({});
	object env;

	if(_status != BATTLE) return 1;	//不用复活了，直接退场
	foreach(object flag in MAP->flags()) {
		if(camp_same(flag, me)) forts += ({ flag });
	}
	if(!sizeof(forts)) forts = MAP->flags();	//如果没有据点可复活，就随机据点复活
	
	env = environment(random1(forts));
	tell_room(env, CYN"\n一股青气飘飘荡荡，慢慢地聚成了一个人的样子。\n"NOR);
	me->move(env);
	return 1;
}


//地狱里凉快，那儿歇着吧
int room_goto_hell(object who)
{	
	mapping buff = ([
		"id"		: WAIT4R,
		"name"		: HIW"等待复活"NOR,
		"comment"	: "你在地狱你耐心等待重回人间。",
		"duration"	: WAIT4DURATION,
		"post_act"	: (: revive_act :),
	]);
	HP->full(who, 1);		//不回复内力，让他在危险中打坐
	HP->add_force(who, DEAD_RECOVER);
	HP->add_mana(who, DEAD_RECOVER);
	BUFF->add(who, buff);
	
	
	who->set_temp("last_damage_from", 0);
	who->remove_all_killer();	
	all_inventory(environment(who))->remove_killer(who);
	who->delete_temp("no_move");
	who->start_busy(1);

	who->move(HELL);
	return 1;
}

//出去吧
int room_get_out(object who)
{
	HP->full(who);
		
	who->remove_all_killer();
	who->set_leader(0);
	BUFF->clear(who);
	HP->full(who);

	who->move(PLACE->random_room1("/d/city"));
	who->start_busy(2);
	return 1;
}



//凶手/受害者获得奖励/惩罚
private int room_kill_reward(object killer, object victim)
{
	int ratio = HP->eval(victim) * 100 / HP->eval(killer);
	int pot = KILL_POT;
	//奖励
	ratio = truncate(ratio, MIN_RATIO, MAX_RATIO);
	trace("ratio: " + ratio, killer);
	pot = pot * ratio / 100;
	score_add_exp(killer, pot);
	//惩罚
	pot = pot * DIE_PER / 100;
	score_add_exp(victim, pot);

	return 1;
}


//玩家被杀
int room_player_die(object env, object victim)
{
	int vc = camp_id(victim);
	int kc = 0;
	object killer = victim->query_temp("last_damage_from");
	
	if(!vc) return room_get_out(victim);
	if(killer) kc = camp_id(killer);

	score_add(victim, "die", 1);

	if(kc) {		
		if(vc != kc) {	//击杀
			room_kill_reward(killer, victim);
			score_add(killer, "kill", 1);
		} else {		//误杀，扣除杀人的基本奖励
			score_add_exp(killer, -KILL_POT/2);
			score_add(killer, "m_kill", 1);
			
			score_add_exp(victim, KILL_POT/2);
		}
	}
	room_goto_hell(victim);
	tell_room(env, CYN + victim->name() + "化作一股青烟，随风飘散。\n"NOR);
	return 1;
}

private void blow_away(object who, object env)
{
	if(environment(who) == env) {
		MAP->blow(who, 3, 2);
	}
}


//检查房间是否过度拥挤，如果是，则吹跑后来者
int room_crowded(object who)
{
	int ret = 0;
	object env = environment(who);
	mapping groups = camp_group(all_inventory(env));

	if(sizeof(groups) < 2) return 0;
	foreach(int c, object* group in groups) {
		int n = sizeof(group) - MATE_PER_ROOM;		
		if(n > 0) {
			object* users = MATH->random_elem(group, n);	
			//users = (c == camp_id(who)) ? ({ who }) : MATH->random_elem(group, n);	//优先吹后来者
			foreach(object u in users) {
				if(!u->is_busy()) u->start_busy(2);
				call_out("blow_away", 1, u, env);
			}
			ret = 1;
		}
	}
	return ret;
}


//某人死亡
int room_sb_die(object env, object who)
{
	who->remove_ride();
	msv("\n$N死了。\n\n", who);
	if(userp(who)) return room_player_die(env, who);
	//npc 死亡
	destruct(who);
	return 1;	
}

//玩家来到新房间
int room_init(object env, object who)
{
	if(wizardp(who) && !camp_id(who)) return 1;
	if(userp(who)) {
		if(!camp_id(who)) return room_get_out(who);
		if(room_crowded(who)) return 1;

		score_add(who, "mp", -1);
		if(who->query("env/invisibility")) score_add(who, "mp", -1);
		
		if(score_query(who, "mp") < 1 && !who->is_busy()) {
			tell_object(who, CYN"\n你跑得太急，一脚踩空摔了个四脚朝天。\n"NOR);
			who->start_busy(MOVE_BUSY);
		}
	}
	return 1;

}

//占领旗子
private int post_climb(mapping climb_buff)
{
	object me = climb_buff["me"];
	object flag = climb_buff["_flag"];
	
	if(_status != BATTLE) return 1;
	if(!same_env(me, flag)) return 1;
	if(me->query("kee") >= climb_buff["_kee"]
		&& !camp_same(me, flag))
	{
		mapping buff = camp_buff(me);

		camp_occupy(flag, camp_id(me), buff["color"]);
		msv(HIC"$N爬到旗杆顶，换上一面战旗。\n"NOR, me);
		
		if(score_query(me, "occupy") < OCCUPY_THR) score_add_exp(me, OCCUPY_POT);
		score_add(me, "occupy", 1);
		rumor("传闻狮驼岭上的" + filter_color(environment(me)->query("short"))
			+ "已经被" + buff["color"] + name_id(me) + HIM"占领了！");
		BUFF->add(flag, ([
			"id"		: BG_NO_RES,
			"name"		: HIY"转换阵营"NOR,
			"comment"	: "转换阵营期间不能提供资源。",
			"duration"	: NO_RES_TIME,
		]));
		return 1;
	}
	if(me->query("kee") < climb_buff["_kee"]) {	//被人打下来了
		object enemy = me->query_temp("last_damage_from");
		if(enemy && !camp_same(me, enemy)) {
			score_add_exp(me, -OCCUPY_POT);
			score_add_exp(enemy, OCCUPY_POT);
			score_add(enemy, "repel", 1);
		}
	}
	msv(CYN"$N从旗杆上摔了下来。\n"NOR, me);

	return 1;
}


//爬旗杆，换军旗，占领据点
int room_climb_flag(object who, object flag)
{
	mapping buff = ([
		"id"		: "climb_flag",
		"name"		: HIY"爬旗杆"NOR,
		"comment"	: "正在往旗杆顶端爬。",
		"duration"	: CLIMB_DURATION,
		"post_act"	: (: post_climb :),
		"_flag"		: flag,
		"_kee"		: who->query("kee"),
	]);
	string msg = BTL->bad_state(who, ({ "busy", "no_move", "invisible" }));
	if(msg) return notify_ok("你" + msg + "。\n");

	if(!camp_buff(who)) return notify_ok("你别捣乱。\n");

	if(BUFF->add(who, buff)) {
		msv(CYN"$N奋力爬向旗杆顶。\n"NOR, who);
		who->start_busy(CLIMB_DURATION);
	}
	return 1;
}
