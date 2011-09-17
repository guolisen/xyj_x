// by firefox 11/21/2009
// 玩家积分

#include "alx.h"

#define SCORE_ID				ALX_PROP
#define ch_dx					COMBAT_D->chinese_daoxing


//获取分数集合
varargs mapping score_entire(object who, int history)
{
	if(history) return DB->query_map(who, SCORE_ID);
	return DB->query_temp_map(who, SCORE_ID);
}

//清除分数集合
varargs mapping score_clear(object who, int history)
{
	if(history) return who->set(SCORE_ID, ([]));
	return who->set_temp(SCORE_ID, ([]));
}

//获取分数
varargs int score_query(object who, string item, int history)
{
	if(history) return who->query(SCORE_ID"/" + item);
	return who->query_temp(SCORE_ID"/" + item);
}

//设置临时分数
void score_set(object who, string item, int value)
{
	who->set_temp(SCORE_ID"/" + item, value);
}


//增加某项分数
varargs int score_add(object who, string item, int value, int history)
{
	if(history) return who->add(SCORE_ID"/" + item, value);
	return who->add_temp(SCORE_ID"/" + item, value);
}

//获取玩家活跃度
varargs int score_liveness(object who, int history)
{
	return score_query(who, "occupy", history) + score_query(who, "repel", history);
}


//增加临时战功
int score_add_exp(object who, int value)
{
	int c = camp_id(who);
	if(c) _camps[c]["exp"] += value;

	tell_object(who, "你得到" + value + "点战功！\n");
	return score_add(who, "exp", value);
}

//增加金钱
int score_add_gold(object who, int value)
{
	who->add("balance", value * 10000);
	tell_object(who, "你得到" + value + "两黄金，已经存入银行！\n");
	return 1;
}

//临时战功加入总战功
void score_add_total(object who)
{
	mapping m0 = score_entire(who, 0);
	mapping m1 = score_entire(who, 1);

	foreach(string k, int v in m0) {
		m1[k] += v;
	}

	tell_object(who, "你累积得到" + m0["exp"] + "点战功！\n");
}

//经验余额
int score_balance(object who)
{
	mapping m = score_entire(who, 1);
	return m["exp"] - m["exp_used"];
}

//经验兑现
int score_use(object who, int pot)
{
	mapping m = score_entire(who, 1);
	
	m["exp_used"] += pot;
	return m["exp"] - m["exp_used"];
}
