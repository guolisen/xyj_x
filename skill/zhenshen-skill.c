// by firefox 07/21/2010
inherit SKILL;

#include <xyj_x.h>

/*

����

���ؼ��ܹ��ã��������������岻ͬ��

*/

//��ȡ��������
mapping query_action(object me, object weapon)
{
    return ZSACT_D->query_attack_act(me);
}

//���и�������
mixed hit_ob(object me, object victim, int damage_bonus)
{
	return ZSACT_D->act_hit_ob(me, victim, damage_bonus);
}

//��ȡ�мܶ���
string query_parry_msg(object weapon)
{
	return ZSACT_D->query_defense_msg();
}

//��ȡ��������
string query_dodge_msg(string limb)
{
	return ZSACT_D->query_defense_msg();
}

int valid_learn(object me)
{
     return notify_fail("��������ͨ��ѧϰ��ߡ�\n");
}

int valid_enable(string usage) 
{ 
	return usage == "unarmed" || usage == "parry"  || usage == "dodge"; 
}

int practice_skill(object me)
{
	return notify_fail("��������ͨ����ϰ��ߡ�\n");
}
