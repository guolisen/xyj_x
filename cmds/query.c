// firefox 03/01/2012

#include <xyj_x.h>
#include <ansi.h>

inherit F_NO_CLEAN_UP;

#define BUFF_ID		"bian2"
#define BUFF_NAME	HIG"变化"NOR
#define DMANA		30		//原法力消耗公式 = 30 + 400 / (spells - 20)


int skill(string arg)
{
}

mapping props = ([

	//hp命令
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

指令格式 ： bian [<人物>|<NPC>|<me>]

变身术，这个指令让你变化成其他人物的模样。是否能变，还要取决于
你的法术和法力大小。

其他相关指令： observe。
HELP
	);
	return 1;
}
