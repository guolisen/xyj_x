// by firefox 03/16/2010

#define NAME		"�׹Ǳ�"	//�����Ӳ������ dodge: -10, parry: -40, damage: 25

inherit SKILL;

mapping *action = ({
	([
		"action"	: "$N����$w���ñ�ֱ��$n��$l��������",
		"dodge"		: -10,
		"parry"		: -40,
		"damage"	: 25,
		"damage_type"	: "����"
	]),
	([
		"action"	: "$N����һת��$w�ó������Ӱ������ʵʵ��Ϯ��$n��$l",
		"dodge"		: -10,
		"parry"		: -40,
		"damage"	: 25,
		"damage_type":	"����"
	]),
	([
		"action"	: "$N����$w������ӰƮ�������ص���$n��$l",
		"dodge"		: -10,
		"parry"		: -40,
		"damage"	: 25,
		"damage_type":	"����"
	]),
});

int valid_learn(object me)
{
	object ob;

	if( (int)me->query("max_force") < 150 )
		return notify_fail("��������������޷���ϰ�޷���\n");

	if( !(ob = me->query_temp("weapon"))
	||	(string)ob->query("skill_type") != "whip" )
		return notify_fail("���������һ�����Ӳ������޷���\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage=="whip" || usage=="parry" || usage=="dodge";
}

int practice_skill(object me)
{
	if( (int)me->query("kee") < 30
	||	(int)me->query("force") < 5 )
		return notify_fail("������������������޷���ϰ�޷���\n");
	me->receive_damage("kee", 30);
	me->add("force", -5);
	write("�㰴����ѧ����һ��޷���\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
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
