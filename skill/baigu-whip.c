// by firefox 03/16/2010

#define NAME		"白骨鞭"	//优秀的硬砍技能 dodge: -10, parry: -40, damage: 25

inherit SKILL;

mapping *action = ({
	([
		"action"	: "$N手中$w抖得笔直向$n的$l连刺数鞭",
		"dodge"		: -10,
		"parry"		: -40,
		"damage"	: 25,
		"damage_type"	: "刺伤"
	]),
	([
		"action"	: "$N身形一转，$w幻出满天鞭影，虚虚实实地袭向$n的$l",
		"dodge"		: -10,
		"parry"		: -40,
		"damage"	: 25,
		"damage_type":	"瘀伤"
	]),
	([
		"action"	: "$N力贯$w，点点鞭影飘浮不定地点向$n的$l",
		"dodge"		: -10,
		"parry"		: -40,
		"damage"	: 25,
		"damage_type":	"刺伤"
	]),
});

int valid_learn(object me)
{
	object ob;

	if( (int)me->query("max_force") < 150 )
		return notify_fail("你的内力不够，无法练习鞭法。\n");

	if( !(ob = me->query_temp("weapon"))
	||	(string)ob->query("skill_type") != "whip" )
		return notify_fail("你必须先找一条鞭子才能练鞭法。\n");

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
		return notify_fail("你的内力或气不够，无法练习鞭法。\n");
	me->receive_damage("kee", 30);
	me->add("force", -5);
	write("你按著所学练了一遍鞭法。\n");
	return 1;
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

string *dodge_msg = ({
     "只见$n一个转身，在$N眼前消失。\n",
     "可是$n身形径向$N飘来，$N这一招竟无着力之处。\n",
     "$n身法轻灵，$N眼一花顿失目标。\n",
     "$n从$N头顶飞过，$N不由得攻势落空！\n",
});

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}
