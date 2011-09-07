
#include "_base.h"

string _format = "%s%-3d%-7s%-20s%8d\n";
string _header = "   ����   ���                ʵ������\n";

//���������������
int get_score(object ob)
{
	int tlvl,i,score;
	string *ski;
	mapping skills = ob->query_skills();
	mapping db = ob->query_entire_dbase();
	
	reset_eval_cost();
	if (!sizeof(skills)) return 1; 
	ski  = keys(skills);
	for(i = 0; i<sizeof(ski); i++) {
		tlvl += skills[ski[i]];
	}
	score = tlvl/(i+1);
	score += db["max_force"]/10;
	score += db["max_mana"]/10;
	score += db["combat_exp"]/5000;
	score += db["daoxing"]/5000;
	return score;
}

//��ѯʵ������threshold���������
varargs mixed* users_score(int threshold)
{
	object* users = children("/obj/user");
	int n = 0;
	
	foreach(object who in users) {		
		if(environment(who) && NWIZARD(who)) {
			int score = get_score(who);
			if(score > threshold)
				_arr[n++] = ({ who, score });
		}
	}
	return sub_arr(_arr, n);
}

//��ѯĳ�������
varargs mixed* family_users(string family)
{
	object* users = children("/obj/user");
	int n = 0;

	foreach(object who in users) {		
		if(environment(who) && NWIZARD(who) && FAMILY->id(who) == family) {
			int score = get_score(who);
			_arr[n++] = ({ who, score });
		}
	}
	return sub_arr(_arr, n);
}

//��ʼ�������Ӱ�
void create()
{
	string* arr = ({"pt", "fc", "wzg", "moon", "jjf", "hell", "lg", "xs", "wdd", "hyd", "psd"});
	
	_lists = ([
		"gs"		: ([
			"header"	: _header,
			"source"	: (: users_score, 5*K :),
			"format"	: (: format, _format :),
		]),
	]);

	foreach(string family in arr) {
		_lists[family] = ([
			"header"	: _header,
			"source"	: (: family_users, family :),
			"format"	: (: format, _format :),
		]);
	}

		/*

	"skill"		: ({ "uforce",		"���ּ��ܰ�" }),
	*/
}
