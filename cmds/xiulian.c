// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>


#define PROP						"sitting"
#define DURATION					60			//����ʱ��
#define DX_GAIN						3100		//300 spells��3��/Сʱ��72��/��

string act_id = "xiudao";
string act_name = "�޵�";
mapping costs = (["kee" : 30, "sen" : 30 ]);
mapping prop_rewards = (["force" : 30 ]);
mapping skill_rewards = (["spells" : 1 ]);
int skill_weak = 0;
int interval = 30;

string start_msg = HIY"$N�����۾�����ϥ���£�����ĬĬ���֪��˵Щʲô��\n"NOR;
string stop_msg = HIY"$N���������۾�������һ����վ��������\n"NOR;

int on_timer(mapping buff);
void on_stop(mapping buff);

int main(object me, string arg)
{
	object env = environment(me);
	
	if(!arg) {
		mapping buff = BUFF->find(me, act_id);
		BUFF->remove1(buff);
	}

	if(env->query("no_fight") || env->query("no_magic"))
		return notify_fail("��ȫ���ڽ�ֹ" + act_name + "��\n");

	if(me->is_busy() || me->query_temp(PROP) || me->is_fighting())
		return notify_fail("��������æ���ء�\n");

	foreach(string k, int v in costs) {
		if(me->query(k) <= v) return notify_fail("��״̬���ѣ��޷�" + act_name + "��\n");
	}
	BUFF->add(me, ([
		"id"			: act_id,
		"name"			: act_name,
		"comment"		: act_name + "������...",
		"temp"			: ([ PROP	: 1]),
		"interval"		: interval,
		"timer_act"		: (: on_timer :),
		"start_msg"		: start_msg,
		"stop_msg"		: stop_msg,
		"post_act"		: (: on_stop :),
		"_before_reward": (: before_reward :),
		"_norm_cost"	: 0,
		"_costs"		: costs,
		"_prop_reward"	: prop_rewards,
		"_skill_reward"	: skill_rewards,
		"_skill_weak"	: skill_weak,
	]));

	me->start_busy(10000);
	return 1;
}

int on_timer(mapping buff)
{
	object me = buff["me"];
	
	if(me->is_fighting()) return 0;
	if(buff["_costs"]) {					//���Լ��
		foreach(string k, int v in buff["_costs"]) {
			if(me->query(k) <= v) return 0;
		}
	}

	if(buff["_before_reward"] && !evaluate(buff["_before_reward"], buff)) return 0;

	if(buff["_costs"]) {					//��������
		foreach(string k, int v in buff["_costs"]) {
			me->add(k, -v);
		}
	}

	if(if(buff["_prop_reward"]) {			//���Խ���
		foreach(string k, int v in buff["_prop_reward"]) {
			me->add(k, v);
		}
	}
	if(if(buff["_skill_reward"]) {			//���ܽ���
		foreach(string k, int v in buff["_skill_reward"]) {
			me->improve_skill(k, v, buff["_skill_"]);
		}
	}
	return 1;
}

void on_stop(mapping buff)
{
	BTL->stop_busy(buff["me"]);
}