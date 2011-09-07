// by firefox 03/16/2010

#define NAME		"紫青剑"	//优秀的硬砍技能 dodge: -40, parry: -10, damage: 25

inherit SKILL;

mapping *action = ({
	([	
		"action"	: "$N淡淡一笑，舞出无数幻影，$n只觉得阵阵幽香四面袭来，却不知该如何闪躲",
		"dodge"		: -30,
		"parry"		: -10,
		"damage"	: 25,
		"damage_type"	:	"刺伤",

		"dodge_power":		10,
		"parry_power":		10,
	]),
	([	
		"action"	: "$N手中$w再一抖，飘浮不定，只看得$n眼花缭乱，哪里还能招架",
		"dodge"		: -30,
		"parry"		: -10,
		"damage"	: 25,
		"damage_type"	:	"刺伤",

		"dodge_power":		10,
		"parry_power":		10,
	]),
	([      
		"action"	: "$n只觉得一缕冷香掠过，$N已悄然间飘至$n身后，剑心直指$n的后胸",  
		"dodge"		: -30,
		"parry"		: -10,
		"damage"	: 25, 
		"damage_type"	:  "刺伤",

		"dodge_power":		10,
		"parry_power":		10,
	]),
	([	//春三十娘杀至尊宝那一剑，百分之一几率出现
		"action"	: "$N冷冷的看着$n，转身要走，突然一挥手剑光已到$n眼前",
		"dodge"		: -60,
		"parry"		: -60,
		"damage"	: 200,
		"damage_type"	:  "刺伤",

		"dodge_power":		10,
		"parry_power":		10,
	]),

});

int valid_learn(object me)
{
	object ob;

	if( (int)me->query("max_force") < 50 )
		return notify_fail("你的内力不够，没有办法练"NAME"剑法。\n");

	if( !(ob = me->query_temp("weapon"))
		||	(string)ob->query("skill_type") != "sword" )
		return notify_fail("你必须先找一把剑才能练剑法。\n");

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
		return notify_fail("你的内力或气不够，没有办法练剑。\n");
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
     "只见$n一个转身，在$N眼前消失。\n",
     "可是$n身形径向$N飘来，$N这一招竟无着力之处。\n",
     "$n身法轻灵，$N眼一花顿失目标。\n",
     "$n从$N头顶飞过，$N不由得攻势落空！\n",
});

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}