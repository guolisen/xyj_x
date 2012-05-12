
#include "_base.h"


string _format = "%s%-3d%-7s%-24s%8d\n";
string _header = "   ����   ���                ";


//��������������ˣ����أ�{who, score}����
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

//��ʼ�������Ӱ�
void create()
{
	mixed* arrs = ({
		({ "rich",	"      �ʲ�",	"balance",		10*K,		K }),
		({ "killer","      ԩ��",	"PKS",			1,			0 }),
		({ "nk",	"   ɱҵ(K)",	"MKS",			K,			10 }),
		({ "mieyao","   ����(K)",	"sys_task/stat/mieyao/num",	K,		0 }),
		({ "quest",	"   ����(K)",	"sys_task/stat/quest/num",	K,		0 }),
		({ "age",	"      ����",	"age",			1,			100 }),

		({ "wx",	"   ��ѧ(M)",	CEXP,			K*K,		10 }),
		({ "dx",	"����(ǧ��)",	DEXP,			K*K,		10 }),
		({ "force",	"  ����(��)",	"maximum_force",100,		10 }),
		({ "mana",	"  ����(��)",	"maximum_mana",	100,		10 }),
		({ "kee",	"  ��Ѫ(K)",		"kee",			1,			K }),
		({ "sen",	"  ����(K)",		"sen",			1,			K }),
		({ "stl",	"  ս��(M)",		"sys_alx/exp",	K*K,		0 }),
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

