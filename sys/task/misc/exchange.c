// by firefox 04/10/2010
// 灭妖任务

#include <xyj_x.h>

inherit TT_BASE;

void create()
{
	init_prop(1000);
}

//向雇主申请任务
varargs int do_reward(object who, string ename, string tname, mapping rewards, int norm_ratio)
{
	mapping m = data_of(who);
	int total = 0;
	mapping tab = ([CEXP : 1, DEXP : 1, PEXP : 4]);
	
	if(!norm_ratio) norm_ratio = 100;

	foreach(string k, int v in rewards) {
		total += tab[k] * v;
		parent()->add_gain(who, k, v);
	}

	//检查配额
	if(!TASK->apply_norm(who, total * norm_ratio / 100)) {
		TASK->tell_tired(0, who);
		return 0;
	}

	//新任务
	m["ename"] = ename;
	m["tname"] = tname;
	m["state"] = "完成";
	m["num"]++;
	
	who->add(_stat_prop + "/num", 1);	
	who->add(_stat_prop + "/done", 1);
	who->add(_stat_prop + "/reward", total);

	return 1;
}

