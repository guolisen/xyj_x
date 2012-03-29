// firefox 03/01/2012

#include <xyj_x.h>
#include <ansi.h>

inherit F_CLEAN_UP;

//查询两属性比率
int query_ratio(string prop0, string prop1, object who)
{
	int i0 = who->query(prop0);
	int i1 = who->query(prop1);
	if(intp(i0) && intp(i1) && i1 != 0) return 100 * i0 / i1;
	return 0;
}

//查询两属性之差
int query_diff(string prop0, string prop1, object who)
{
	int i0 = who->query(prop0);
	int i1 = who->query(prop1);
	if(intp(i0) && intp(i1)) return i0 - i1;
	return 0;
}

//查询技能等级
int skill_level(object who, string skill)
{
	return who->query_skill(skill, 1);
}

//查询技能激发
string skill_map(object who, string skill)
{
	return who->query_skill_mapped(skill);
}

//查询技能学习点数
int skill_learned(object who, string skill)
{
	mapping m = who->query_learned();
	if(!m) return 0;
	return m[skill];
}

//查询任务状态
string task_state(object who, string id)
{
	return who->query(TASK_PROP"/list/" + id + "/state");
}

//查询任务对象
string task_target(object who, string id)
{
	return who->query(TASK_PROP"/list/" + id + "/tname");
}

//查询任务备注
string task_remark(object who, string id)
{
	return who->query(TASK_PROP"/list/" + id + "/remark");
}

//属性对应表
mapping _props = ([

	//hp命令
	"kee"			: "kee",
	"sen"			: "sen",		
	"eff_kee"		: "eff_kee",
	"eff_sen"		: "eff_sen",
	"kee_ratio"		: (: query_ratio, "eff_kee", "max_kee" :),
	"sen_ratio"		: (: query_ratio, "eff_sen", "max_sen" :),
	
	"force"			: "force",
	"mana"			: "mana",
	"max_force"		: "max_force",
	"max_mana"		: "max_mana",
	"force_ratio"	: (: query_ratio, "max_force", "maximum_force" :),
	"mana_ratio"	: (: query_ratio, "max_mana", "maximum_mana" :),

	"food"			: "food",
	"water"			: "water",

	"combat_exp"	: "combat_exp",
	"daoxing"		: "daoxing",

	"potential"		: (: query_diff, "potential", "learned_points" :),

	//score命令
	"title"			: "title",
	"name"			: "name",
	"id"			: "id",
	"age"			: "age",

	"damage"		: "damage",
	"armor"			: "armor",
	"family"		: "family/family_name",
	"master"		: "family/master_name",

	"balance"		: "balance",

	//skills
	
	"skill_level"	: (: skill_level :),
	"skill_learned"	: (: skill_learned :),
	"skill_map"		: (: skill_map :),

	//tasks
	
	"task_norm"		: TASK_PROP"/norm",
	"task_state"	: (: task_state :),
	"task_target"	: (: task_target :),
	"task_remark"	: (: task_remark :),	//quest/food

]);


int main(object me, string arg)
{
	string title = "属性值";
	mixed result = 0;
	string* arr;
		
	if(!arg) arg = "";
	sscanf(arg, "%s %s", title, arg);

	arr = explode(arg, ",");
	
	write("\n" + title + ":");
	foreach(string str in arr) {
		string fun, args;
		
		result = 0;
		if(sscanf(str, "%s(%s)", fun, args) == 2) {
			function f = _props[fun];
			if(functionp(f)) result = evaluate(f, me, args);
		} else {
			mixed v = _props[str];
			if(functionp(v)) result = evaluate(v, me);
			if(stringp(v)) result = me->query(v);
		}
		write(result + ",");
	}
	write("\n");

	return intp(result) ? result : 1;
}

int help(object me)
{
	write(@HELP

指令格式 ： query [标题] <属性>|<属性列表>

查询自身的属性或属性列表（以逗号分隔），显示被查询属性的值，命令返回最后一个属性
的值，如果值为字符串，则返回1。该指令旨在减少带宽占用，思想源自北大侠客行。

hp相关属性
- 气血/精神：kee sen eff_kee eff_sen kee_ratio sen_ratio 
- 内力/法力：force mana max_force max_mana force_ratio mana_ratio
- 食物/饮水：food water
- 经验/潜能：combat_exp daoxing potential

score相关属性
- 名称/头衔：title name id
- 攻击/防护：damage armor
- 门派/师承：family master
- 其他：     balance age

skills相关属性
- 技能等级：skill_level(技能)
- 学习点：  skill_learned(技能)
- 技能激发：skill_map(技能)
技能为技能id，比如unarmed。

tasks相关属性
- 任务额度：task_norm
- 任务状态：task_state(任务)
- 任务目标：task_target(任务)
- 任务备注：task_remark(任务)
任务格式为：<任务类别>/<任务>，类别和任务如下：
- 灭妖(mieyao)：mieyao
- 解谜(quest)：food，weapon，armor，cloth，ask，give，kill
- 势力(forces)：cien
比如李靖任务为：mieyao/mieyao，猪八戒任务为：quest/food。

用法举例
- 查看气血：query 气血 kee,eff_kee,kee_ratio
- 查看技能：query 技能 skill_level(force),skill_level(spells)
- 查看任务：query task_target(quest/food),task_state(quest/food)
HELP
	);
	return 1;
}
