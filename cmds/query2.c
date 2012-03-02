// firefox 03/01/2012

#include <xyj_x.h>
#include <ansi.h>

inherit F_CLEAN_UP;


int query_ratio(string prop0, string prop1, object who)
{
	int i0 = who->query(prop0);
	int i1 = who->query(prop1);
	if(intp(i0) && intp(i1) && i1 != 0) return 100 * i0 / i1;
	return 0;
}

int skill_level(object who, string skill)
{
	return who->query_skill(skill, 1);
}

string skill_map(object who, string skill)
{
	return who->query_skill_mapped(skill);
}

int skill_learned(object who, string skill)
{
	mapping m = who->query_learned();
	if(!m) return 0;
	return m[skill];
}

string task_state(object who, string id)
{
	return who->query(TASK_PROP"/list/" + id + "/state");
}

string task_target(object who, string id)
{
	return who->query(TASK_PROP"/list/" + id + "/tname");
}

string task_remark(object who, string id)
{
	return who->query(TASK_PROP"/list/" + id + "/remark");
}

mapping _props = ([

	//hp����
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

	"potential"		: "learned_points",

	//score����
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
	mixed result = 0;
	string* arr;
		
	if(!arg) arg = "";
	arr = explode(arg, ",");
	
	write("\n����ֵ:");
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
		write(result + ";");
	}
	write("\n");

	return intp(result) ? result : 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ �� query <����> �� query <�����б�>

��ѯ��������Ի������б��Զ��ŷָ�������ʾ����ѯ���Ե�ֵ����������һ������
��ֵ�����ֵΪ�ַ������򷵻�1����ָ��ּ�ڼ��ٴ���ռ�ã�˼��Դ�Ա��������С�

hp�������
- ��Ѫ/����kee sen eff_kee eff_sen kee_ratio sen_ratio 
- ����/������force mana max_force max_mana force_ratio mana_ratio
- ʳ��/��ˮ��food water
- ����/Ǳ�ܣ�combat_exp daoxing potential

score�������
- ����/ͷ�Σ�title name id
- ����/������damage armor
- ����/ʦ�У�family master
- ������     balance age

skills�������
- ���ܵȼ���skill_level(����)
- ѧϰ�㣺  skill_learned(����)
- ���ܼ�����skill_map(����)
����Ϊ����id������unarmed��

tasks�������
- �����ȣ�task_norm
- ����״̬��task_state(����)
- ����Ŀ�꣺task_target(����)
- ����ע��task_remark(����)
�����ʽΪ��<�������>/<����>�������������£�
- ����(mieyao)��mieyao
- ����(quest)��food��weapon��armor��cloth��ask��give��kill
- ����(forces)��cien
���������Ϊ��mieyao/mieyao����˽�����Ϊ��quest/food��

HELP
	);
	return 1;
}
