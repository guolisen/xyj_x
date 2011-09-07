// by firefox 11/21/2009

#include <xyj_x.h>

//��ȡ��ߵȼ�
int max_level(object who)
{
	int n = 0;
	mapping skills = who->query_skills();
	if(!mapp(skills)) return 0;
	foreach(string skill, int level in skills) {
		if(level > n) n = level;
	}
	return n;
}

//��ȡƽ���ȼ�
int avg_level(object who)
{
	int sum = 0;
	mapping skills = who->query_skills();
	if(!mapp(skills) || !sizeof(skills)) return 0;
	foreach(string skill, int level in skills) {
		sum += level;
	}
	return sum / sizeof(skills);
}

//ΪĿ�����ó�ʼ��skills������("hellfire-whip",	160,"whip",160,"parry",120)
void set_list(object who, mixed* list)
{
	foreach(mixed* arr in list) {
		who->set_skill(arr[0], arr[1]);
		for(int i = 2; i < sizeof(arr); i += 2) {
			who->set_skill(arr[i], arr[i + 1]);
			who->map_skill(arr[i], arr[0]);
		}
	}
}

//ΪĿ�����ó�ʼ��skills��ͬһ�ȼ�������({kugu-blade, blade, dodge})
void set_list2(object who, mixed* list, int level)
{
	foreach(mixed* arr in list) {
		who->set_skill(arr[0], level);
		for(int i = 1; i < sizeof(arr); i += 1) {
			who->set_skill(arr[i], level);
			who->map_skill(arr[i], arr[0]);
		}
	}
}


//ΪĿ������skills�ȼ�
void set_level(object who, int level)
{
	mapping skills = who->query_skills();
	foreach(string skill in keys(skills)) {
		skills[skill] = level;
	}
}

//skill������Ч�ȼ�������װ������ֵ
int basic_level(object who, string id)
{
	int lvl = who->query_skill(id, 1) / 2
		+ who->query_skill(who->query_skill_mapped(id), 1);
	return lvl;
}

//skill���Ƶ��������
int max_force(object who)
{
	return basic_level(who, "force") * 10;
}


//skill���Ƶ������
int max_mana(object who)
{
	return basic_level(who, "spells") * 10;
}

//���ȫ��skill
void clear_all(object who)
{
	mapping skills = who->query_skills();
	mapping mapped = who->query_skill_map();
	
	if(skills) {
		foreach(string skill in keys(skills)) {
			who->delete_skill(skill);
		}
	}
	if(mapped) {
		foreach(string skill in keys(mapped)) {
			who->map_skill(skill, 0);
		}
	}
}

#define SKILL_PATH				X_DIR"skill/"
//ʩ��skill����
int do_act(string type, string arg, string fmt, string basic_skill, string env_flag)
{
	object me = this_player();
	object target;
	string skill, act, id, file;

	if(me->is_busy() || !arg || environment(me)->query(env_flag)) return 0;

	if(sscanf(arg, fmt, act, id) == 2) {
		target = present(id, environment(me));
		if(!target) return 0;
	} else {
		act = arg;
	}

	skill = me->query_skill_mapped(basic_skill);
	if(!stringp(skill)) return 0;

	file = SKILL_PATH + skill + "/" + act;
	if(file_size(file + ".c") <= 0 ) return 0;

	return (int)call_other(file, type, me, target);
}
