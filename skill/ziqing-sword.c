// by firefox 03/16/2010

#define NAME		"���ལ"	//�����Ӳ������ dodge: -40, parry: -10, damage: 25

inherit SKILL;

mapping *action = ({
	([	
		"action"	: "$N����һЦ�����������Ӱ��$nֻ����������������Ϯ����ȴ��֪���������",
		"dodge"		: -30,
		"parry"		: -10,
		"damage"	: 25,
		"damage_type"	:	"����",

		"dodge_power":		10,
		"parry_power":		10,
	]),
	([	
		"action"	: "$N����$w��һ����Ʈ��������ֻ����$n�ۻ����ң����ﻹ���м�",
		"dodge"		: -30,
		"parry"		: -10,
		"damage"	: 25,
		"damage_type"	:	"����",

		"dodge_power":		10,
		"parry_power":		10,
	]),
	([      
		"action"	: "$nֻ����һ�������ӹ���$N����Ȼ��Ʈ��$n��󣬽���ֱָ$n�ĺ���",  
		"dodge"		: -30,
		"parry"		: -10,
		"damage"	: 25, 
		"damage_type"	:  "����",

		"dodge_power":		10,
		"parry_power":		10,
	]),
	([	//����ʮ��ɱ������һ�����ٷ�֮һ���ʳ���
		"action"	: "$N����Ŀ���$n��ת��Ҫ�ߣ�ͻȻһ���ֽ����ѵ�$n��ǰ",
		"dodge"		: -60,
		"parry"		: -60,
		"damage"	: 200,
		"damage_type"	:  "����",

		"dodge_power":		10,
		"parry_power":		10,
	]),

});

int valid_learn(object me)
{
	object ob;

	if( (int)me->query("max_force") < 50 )
		return notify_fail("�������������û�а취��"NAME"������\n");

	if( !(ob = me->query_temp("weapon"))
		||	(string)ob->query("skill_type") != "sword" )
		return notify_fail("���������һ�ѽ�������������\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage=="sword" || usage=="parry" || usage=="dodge";
}

int practice_skill(object me)
{
	if( (int)me->query("kee") < 30
		||	(int)me->query("force") < 3 )
		return notify_fail("�����������������û�а취������\n");
	me->receive_damage("kee", 30);
	me->add("force", -3);
	return 1;
}

mapping query_action(object me, object weapon)
{
	int last = sizeof(action) - 1;
	if(!random(1000)) return action[last];
	return action[random(last)];
}

string *dodge_msg = ({
     "ֻ��$nһ��ת����$N��ǰ��ʧ��\n",
     "����$n���ξ���$NƮ����$N��һ�о�������֮����\n",
     "$n�����飬$N��һ����ʧĿ�ꡣ\n",
     "$n��$Nͷ���ɹ���$N���ɵù�����գ�\n",
});

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}