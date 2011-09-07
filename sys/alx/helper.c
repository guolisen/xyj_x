// by firefox 11/21/2009
// 救命毫毛/玩家护法

#include "alx.h"

mapping _helper	= ([]);							//记录玩家最高数据


void help_init()
{
	_helper	= ([ CEXP : 2*K*K, DEXP : 2*K*K, "skill" : 200, "max_kee" : 2000, "max_sen" : 2000 ]);
}


//记录玩家最高数据
void help_record_top(object who)
{
	mapping db = who->query_entire_dbase();

	_helper[CEXP] = max2(_helper[CEXP], db[CEXP]);
	_helper[DEXP] = max2(_helper[DEXP], db[DEXP]);
	_helper["max_kee"] = max2(_helper["max_kee"], db["max_kee"]);
	_helper["max_sen"] = max2(_helper["max_sen"], db["max_sen"]);
	_helper["max_force"] = max2(_helper["max_force"], db["max_force"]);
	_helper["max_mana"] = max2(_helper["max_mana"], db["max_mana"]);
	_helper["skill"] = max2(_helper["skill"], SKI->max_level(who));
	
	trace("top skill:" + _helper["skill"], who);
}

//玩家平均收益
private int camp_res(mapping c)
{
	int n = sizeof(c["users"]);
	return c["res"] + c["exp"] / max2(n, 1);
}

//分发救命毫毛
void help_allot_hair()
{
	mapping tab = ([]);
	int res1 = camp_res(_camps[XIAN]);
	int res2 = camp_res(_camps[MO]);

	int res_thr = 200 + (res1 + res2) * 6 / 10;
	int c = 0;
	int n = sizeof(_camps[XIAN]["users"]) + sizeof(_camps[MO]["users"]);

	//资源6:4，则强势阵营没毫毛
	if(res1 > res_thr) c = MO;
	if(res2 > res_thr) c = XIAN;

	//否则随机选择一个阵营
	if(!c) c = random(2) ? XIAN : MO;

	foreach(object user in _camps[c]["users"]) {
		if(user && interactive(user)) {
			//倾向于发给参与攻守的玩家
			int score = 1 + score_liveness(user);
			int ev = HP->eval(user);
			score = truncate(score, 1, 2);
			ev = max2(ev, K);

			tab[user] = score * K * K / ev;	//概率与评价反比，与功绩正比
		}
	}
	if(!sizeof(tab)) return;
	n = 1 + n / 15;
	for(int i = 0; i < n; ++i) {
		object winner = roulette(tab);
		if(winner) {
			object hair = new(__DIR__"helper/hair");
			BUFF->start_life(hair, 300);
			if(!hair->move(winner)) destruct(hair);
		}
		reset_eval_cost();
	}
}

//玩家求救
int help_me(object who)
{
	string id = FAMILY->id(who);
	int camp = camp_id(who);
	object hufa;
	//todo:救命毫毛是变身状态，和其他变身互斥。
	if(!camp) return 1;

	if(!id || !random(10)) id = random1(({"pig", "xiand", "rjd", "normal", "fmm"}));

	hufa = new(__DIR__"helper/m_" + id);
	if(!hufa) return -1;
	else {		
		int duration = HELPER_LIFE;
		mapping db = hufa->query_entire_dbase();

		//增加玩家血量
		BUFF->start_add_kee(who, _helper["max_kee"] * HAIR_HP_MULT, duration);
		BUFF->start_add_sen(who, _helper["max_sen"] * HAIR_HP_MULT, duration);
		
		//召唤护法
		set_camp(hufa, camp);
		hufa->invocation(who, duration);

		db[CEXP]		= _helper[CEXP] / 100 * HELPER_RATIO;
		db[DEXP]		= _helper[DEXP] / 100 * HELPER_RATIO;
		db["max_kee"]	= _helper["max_kee"];
		db["max_sen"]	= _helper["max_sen"];
		db["max_force"]	= _helper["max_force"] * HELPER_RATIO / 100;
		db["max_mana"]	= _helper["max_mana"] * HELPER_RATIO / 100;
		
		SKI->set_level(hufa, _helper["skill"] * HELPER_RATIO / 100);
		HP->full(hufa);

		HP->full(who);
	}
	return 1;
}


