// by firefox 07/21/2010
inherit SKILL;

#include <xyj_x.h>

/*

真身技

防守技能公用，攻击技能随种族不同。

*/

//获取攻击动作
mapping query_action(object me, object weapon)
{
    return ZSACT_D->query_attack_act(me);
}

//击中附带动作
mixed hit_ob(object me, object victim, int damage_bonus)
{
	return ZSACT_D->act_hit_ob(me, victim, damage_bonus);
}

//获取招架动作
string query_parry_msg(object weapon)
{
	return ZSACT_D->query_defense_msg();
}

//获取躲闪动作
string query_dodge_msg(string limb)
{
	return ZSACT_D->query_defense_msg();
}

int valid_learn(object me)
{
     return notify_fail("真身技不能通过学习提高。\n");
}

int valid_enable(string usage) 
{ 
	return usage == "unarmed" || usage == "parry"  || usage == "dodge"; 
}

int practice_skill(object me)
{
	return notify_fail("真身技不能通过练习提高。\n");
}
