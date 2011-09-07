// by firefox 04/10/2010
// ��������

#include <xyj_x.h>

inherit TT_BASE;

void create()
{
	init_prop(1000);
}

//�������������
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

	//������
	if(!TASK->apply_norm(who, total * norm_ratio / 100)) {
		TASK->tell_tired(0, who);
		return 0;
	}

	//������
	m["ename"] = ename;
	m["tname"] = tname;
	m["state"] = "���";
	m["num"]++;
	
	who->add(_stat_prop + "/num", 1);	
	who->add(_stat_prop + "/done", 1);
	who->add(_stat_prop + "/reward", total);

	return 1;
}

