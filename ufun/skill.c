// by firefox 11/21/2009

#include <xyj_x.h>

//获取最高等级
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

//获取平均等级
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

//为目标设置初始化skills，技能("hellfire-whip",	160,"whip",160,"parry",120)
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

//为目标设置初始化skills到同一等级，技能({kugu-blade, blade, dodge})
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


//为目标设置skills等级
void set_level(object who, int level)
{
	mapping skills = who->query_skills();
	foreach(string skill in keys(skills)) {
		skills[skill] = level;
	}
}

//skill基本有效等级，忽略装备附加值
int basic_level(object who, string id)
{
	int lvl = who->query_skill(id, 1) / 2
		+ who->query_skill(who->query_skill_mapped(id), 1);
	return lvl;
}

//skill限制的最大内力
int max_force(object who)
{
	return basic_level(who, "force") * 10;
}


//skill限制的最大法力
int max_mana(object who)
{
	return basic_level(who, "spells") * 10;
}

//清除全部skill
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
//施放skill招数
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
