
#include "alx.h"


//����
private int revive_act(mapping buff)
{
	object me = buff["me"];
	object* forts = ({});
	object env;

	if(_status != BATTLE) return 1;	//���ø����ˣ�ֱ���˳�
	foreach(object flag in MAP->flags()) {
		if(camp_same(flag, me)) forts += ({ flag });
	}
	if(!sizeof(forts)) forts = MAP->flags();	//���û�оݵ�ɸ��������ݵ㸴��
	
	env = environment(random1(forts));
	tell_room(env, CYN"\nһ������ƮƮ�����������ؾ۳���һ���˵����ӡ�\n"NOR);
	me->move(env);
	return 1;
}


//���������죬�Ƕ�Ъ�Ű�
int room_goto_hell(object who)
{	
	mapping buff = ([
		"id"		: WAIT4R,
		"name"		: HIW"�ȴ�����"NOR,
		"comment"	: "���ڵ��������ĵȴ��ػ��˼䡣",
		"duration"	: WAIT4DURATION,
		"post_act"	: (: revive_act :),
	]);
	HP->full(who, 1);		//���ظ�������������Σ���д���
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

//��ȥ��
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



//����/�ܺ��߻�ý���/�ͷ�
private int room_kill_reward(object killer, object victim)
{
	int ratio = HP->eval(victim) * 100 / HP->eval(killer);
	int pot = KILL_POT;
	//����
	ratio = truncate(ratio, MIN_RATIO, MAX_RATIO);
	trace("ratio: " + ratio, killer);
	pot = pot * ratio / 100;
	score_add_exp(killer, pot);
	//�ͷ�
	pot = pot * DIE_PER / 100;
	score_add_exp(victim, pot);

	return 1;
}


//��ұ�ɱ
int room_player_die(object env, object victim)
{
	int vc = camp_id(victim);
	int kc = 0;
	object killer = victim->query_temp("last_damage_from");
	
	if(!vc) return room_get_out(victim);
	if(killer) kc = camp_id(killer);

	score_add(victim, "die", 1);

	if(kc) {		
		if(vc != kc) {	//��ɱ
			room_kill_reward(killer, victim);
			score_add(killer, "kill", 1);
		} else {		//��ɱ���۳�ɱ�˵Ļ�������
			score_add_exp(killer, -KILL_POT/2);
			score_add(killer, "m_kill", 1);
			
			score_add_exp(victim, KILL_POT/2);
		}
	}
	room_goto_hell(victim);
	tell_room(env, CYN + victim->name() + "����һ�����̣����Ʈɢ��\n"NOR);
	return 1;
}

private void blow_away(object who, object env)
{
	if(environment(who) == env) {
		MAP->blow(who, 3, 2);
	}
}


//��鷿���Ƿ����ӵ��������ǣ����ܺ�����
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
			//users = (c == camp_id(who)) ? ({ who }) : MATH->random_elem(group, n);	//���ȴ�������
			foreach(object u in users) {
				if(!u->is_busy()) u->start_busy(2);
				call_out("blow_away", 1, u, env);
			}
			ret = 1;
		}
	}
	return ret;
}


//ĳ������
int room_sb_die(object env, object who)
{
	who->remove_ride();
	msv("\n$N���ˡ�\n\n", who);
	if(userp(who)) return room_player_die(env, who);
	//npc ����
	destruct(who);
	return 1;	
}

//��������·���
int room_init(object env, object who)
{
	if(wizardp(who) && !camp_id(who)) return 1;
	if(userp(who)) {
		if(!camp_id(who)) return room_get_out(who);
		if(room_crowded(who)) return 1;

		score_add(who, "mp", -1);
		if(who->query("env/invisibility")) score_add(who, "mp", -1);
		
		if(score_query(who, "mp") < 1 && !who->is_busy()) {
			tell_object(who, CYN"\n���ܵ�̫����һ�Ųȿ�ˤ�˸��Ľų��졣\n"NOR);
			who->start_busy(MOVE_BUSY);
		}
	}
	return 1;

}

//ռ������
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
		msv(HIC"$N������˶�������һ��ս�졣\n"NOR, me);
		
		if(score_query(me, "occupy") < OCCUPY_THR) score_add_exp(me, OCCUPY_POT);
		score_add(me, "occupy", 1);
		rumor("����ʨ�����ϵ�" + filter_color(environment(me)->query("short"))
			+ "�Ѿ���" + buff["color"] + name_id(me) + HIM"ռ���ˣ�");
		BUFF->add(flag, ([
			"id"		: BG_NO_RES,
			"name"		: HIY"ת����Ӫ"NOR,
			"comment"	: "ת����Ӫ�ڼ䲻���ṩ��Դ��",
			"duration"	: NO_RES_TIME,
		]));
		return 1;
	}
	if(me->query("kee") < climb_buff["_kee"]) {	//���˴�������
		object enemy = me->query_temp("last_damage_from");
		if(enemy && !camp_same(me, enemy)) {
			score_add_exp(me, -OCCUPY_POT);
			score_add_exp(enemy, OCCUPY_POT);
			score_add(enemy, "repel", 1);
		}
	}
	msv(CYN"$N�������ˤ��������\n"NOR, me);

	return 1;
}


//����ˣ������죬ռ��ݵ�
int room_climb_flag(object who, object flag)
{
	mapping buff = ([
		"id"		: "climb_flag",
		"name"		: HIY"�����"NOR,
		"comment"	: "��������˶�������",
		"duration"	: CLIMB_DURATION,
		"post_act"	: (: post_climb :),
		"_flag"		: flag,
		"_kee"		: who->query("kee"),
	]);
	string msg = BTL->bad_state(who, ({ "busy", "no_move", "invisible" }));
	if(msg) return notify_ok("��" + msg + "��\n");

	if(!camp_buff(who)) return notify_ok("����ҡ�\n");

	if(BUFF->add(who, buff)) {
		msv(CYN"$N����������˶���\n"NOR, who);
		who->start_busy(CLIMB_DURATION);
	}
	return 1;
}
