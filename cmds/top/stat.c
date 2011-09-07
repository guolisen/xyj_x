
#include "_base.h"

#define	NAME		0
#define	SUM			1
#define	PCT			2

string _format = "%s%-3d%-20s%8d%10d\n";
string _header = "   ����                �ۼ�ʵ��    �ٷֱ�\n";

//�Ƚ�
int cmp_sum(mixed* m1, mixed* m2)
{
	return m2[SUM] - m1[SUM];
}

//��ʽ���񵥵�һ�����
string format1(mixed* arr, int i)
{
	string* colors = ({NOR, YEL});
	
	return sprintf(_format,
		colors[i % 2],
		i + 1,
		or2(arr[NAME], "����"),
		arr[SUM],
		arr[PCT],
		);
}

//mapת����array
mixed* m2arr(mapping m)
{
	int i = 0;
	int sum = 0;
	mixed* arr = allocate(sizeof(m));

	foreach(string k, int v in m) {
		sum += v;
	}
	if(sum < 1) sum = 1;
	foreach(string k, int v in m) {
		arr[i++] = ({ k, v, 100 * v / sum });
	}
	return arr;
}

int exp_sum(object who)
{
	mapping db = who->query_entire_dbase();
	return db[CEXP] / K + db[DEXP] / K + db[PEXP] * 4 / K;
}


//ͳ������
mixed* stat_mp()
{
	object* users = children("/obj/user");
	mapping m = ([]);	
	foreach(object who in users) {
		if(environment(who) && NWIZARD(who)) {
			string family = who->query("family/family_name");
			m[family] += exp_sum(who);
		}
	}
	return m2arr(m);
}

//ͳ�Ƽ���
mixed* stat_skill(string skill)
{
	object* users = children("/obj/user");
	mapping m = ([]);	
	foreach(object who in users) {
		if(environment(who) && NWIZARD(who)) {
			string s = who->query_skill_mapped(skill);
			if(s) m[s] +=  exp_sum(who);
		}
	}
	return m2arr(m);
}

//ͳ������
mixed* stat_wq()
{
	object* users = children("/obj/user");
	mapping m = ([]);
	foreach(object who in users) {
		if(environment(who) && NWIZARD(who)) {
			object weapon = who->query_temp("weapon");
			string s = weapon ? weapon->query("skill_type") : "unarmed";
			if(s) m[s] +=  exp_sum(who);
		}
	}
	return m2arr(m);
}

//��ʼ�������Ӱ�
void create()
{
	mapping funs = ([
		"mp"		: (: stat_mp :),
		"sforce"	: (: stat_skill, "force" :),
		"spells"	: (: stat_skill, "spells" :),
		"dodge"		: (: stat_skill, "dodge" :),
		"wq"		: (: stat_wq :),
	]);
	_lists = ([]);

	foreach(string id, mixed fun in funs) {
		_lists[id] = ([
			"header"	: _header,
			"source"	: fun,
			"format"	: (: format1 :),
		]);
	}
}

