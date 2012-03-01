// firefox 03/01/2012

#include <xyj_x.h>
#include <ansi.h>

inherit F_NO_CLEAN_UP;

#define BUFF_ID		"bian2"
#define BUFF_NAME	HIG"�仯"NOR
#define DMANA		30		//ԭ�������Ĺ�ʽ = 30 + 400 / (spells - 20)


int skill(string arg)
{
}

mapping props = ([

	//hp����
	"kee"			: "kee",
	"sen"			: "sen",		
	"eff_kee"		: "eff_kee",
	"eff_sen"		: "eff_sen",
	"kee_ratio"		: "eff_kee",
	"sen_ratio"		: "eff_sen",
	
	"force"			: "force",
	"mana"			: "mana",
	"max_force"		: "max_force",
	"max_mana"		: "max_mana",
	"force_ratio"	: "force_ratio",
	"mana_ratio"	: "mana_ratio",

	"food"			: "food",
	"water"			: "water",
	"max_food"		: "max_food",
	"max_water"		: "max_water",

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
	
	"skill_level"	: (: skill :),
	"skill_learned"	: (: skill :),
	"skill_map"		: (: skill :),

	//tasks

	"task_name"		: (: skill :),	//quest/food
	"task_state"	: (: skill :),
	"task_target"	: (: skill :),

]);


int main(object me, string arg)
{
	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ �� bian [<����>|<NPC>|<me>]

�����������ָ������仯�����������ģ�����Ƿ��ܱ䣬��Ҫȡ����
��ķ����ͷ�����С��

�������ָ� observe��
HELP
	);
	return 1;
}
