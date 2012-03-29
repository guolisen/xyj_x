// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>


#define PROP						"sitting"
#define DURATION					60			//单次时间
#define DX_GAIN						3100		//300 spells，3年/小时，72年/天

string act_id = "xiudao";
string act_name = "修道";
mapping costs = (["kee" : 30, "sen" : 30 ]);
mapping prop_rewards = (["force" : 30 ]);
mapping skill_rewards = (["spells" : 1 ]);
int skill_weak = 0;
int interval = 30;

string start_msg = HIY"$N闭上眼睛，盘膝坐下，嘴里默默念念不知在说些什么。\n"NOR;
string stop_msg = HIY"$N缓缓睁开眼睛，长舒一口气站了起来。\n"NOR;

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
		return notify_fail("安全区内禁止" + act_name + "。\n");

	if(me->is_busy() || me->query_temp(PROP) || me->is_fighting())
		return notify_fail("你现在正忙着呢。\n");

	foreach(string k, int v in costs) {
		if(me->query(k) <= v) return notify_fail("你状态不佳，无法" + act_name + "。\n");
	}
	BUFF->add(me, ([
		"id"			: act_id,
		"name"			: act_name,
		"comment"		: act_name + "进行中...",
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
	if(buff["_costs"]) {					//属性检查
		foreach(string k, int v in buff["_costs"]) {
			if(me->query(k) <= v) return 0;
		}
	}

	if(buff["_before_reward"] && !evaluate(buff["_before_reward"], buff)) return 0;

	if(buff["_costs"]) {					//属性消耗
		foreach(string k, int v in buff["_costs"]) {
			me->add(k, -v);
		}
	}

	if(if(buff["_prop_reward"]) {			//属性奖励
		foreach(string k, int v in buff["_prop_reward"]) {
			me->add(k, v);
		}
	}
	if(if(buff["_skill_reward"]) {			//技能奖励
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