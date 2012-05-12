
#include "_base.h"


string _format = "%s%-3d%-7s%-24s%8d\n";
string _header = "   门派   玩家                ";


//计算分数，并过滤，返回：{who, score}数组
varargs mixed* calc_scores(string prop, int unit, int threshold)
{
	object* users = children("/obj/user");
	int n = 0;

	if(!unit) unit = 1;
	
	foreach(object who in users) {		
		if(environment(who) && NWIZARD(who)) {			
			int score = who->query(prop) / unit;
			if(score > threshold)
				_arr[n++] = ({ who, score });
		}
	}
	return sub_arr(_arr, n);
}

//初始化各个子榜单
void create()
{
	mixed* arrs = ({
		({ "rich",	"      资产",	"balance",		10*K,		K }),
		({ "killer","      冤魂",	"PKS",			1,			0 }),
		({ "nk",	"   杀业(K)",	"MKS",			K,			10 }),
		({ "mieyao","   灭妖(K)",	"sys_task/stat/mieyao/num",	K,		0 }),
		({ "quest",	"   解谜(K)",	"sys_task/stat/quest/num",	K,		0 }),
		({ "age",	"      高寿",	"age",			1,			100 }),

		({ "wx",	"   武学(M)",	CEXP,			K*K,		10 }),
		({ "dx",	"道行(千年)",	DEXP,			K*K,		10 }),
		({ "force",	"  内力(年)",	"maximum_force",100,		10 }),
		({ "mana",	"  法力(年)",	"maximum_mana",	100,		10 }),
		({ "kee",	"  气血(K)",		"kee",			1,			K }),
		({ "sen",	"  精神(K)",		"sen",			1,			K }),
		({ "stl",	"  战功(M)",		"sys_alx/exp",	K*K,		0 }),
	});

	_lists = ([]);

	foreach(mixed* arr in arrs) {
		_lists[arr[0]] = ([
			"header"	: _header + arr[1] + "\n",
			"source"	: (: calc_scores, arr[2], arr[3], arr[4] :),
			"format"	: (: format, _format :),
		]);
	}	
}

