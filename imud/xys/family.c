// by firefox 10/01/2010
// 西游杀-技能

#include "uskill.c"

//门派技能
mapping _family_skills = ([

	"南海普陀山"	: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"staff"		: 100,	
	]),
	"方寸山三星洞"	: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"sword"		: 100,	"stick"		: 100,
	]),
	"五庄观"		: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"sword"		: 100,	"hammer"	: 100,	"blade"		: 100,
	]),
	"月宫"		: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 120,	"parry"		: 100,
		"unarmed"	: 80,	"sword"		: 100,	"whip"		: 100,
	]),

	"将军府"		: ([
		"force"		: 100,	"spells"	: 80,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"mace"		: 120,	"axe"		: 120,	"spear"		: 120,		
	]),
	"阎罗地府"	: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"sword"		: 100,	"stick"		: 100,	"whip"		: 100,		
	]),
	"东海龙宫"	: ([
		"force"		: 100,	"spells"	: 75,	"dodge"		: 75,	"parry"		: 100,
		"unarmed"	: 150,	"hammer"	: 100,	"fork"		: 100,
	]),
	"大雪山"		: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"sword"		: 100,	"blade"		: 100,
	]),
	"陷空山无底洞"	: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"sword"		: 100,	"blade"		: 100,
	]),
	"火云洞"		: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"stick"		: 100,	"fork"		: 100,	"spear"		: 100,
	]),
	"盘丝洞"		: ([
		"force"		: 100,	"spells"	: 120,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 80,	"sword"		: 100,	"whip"		: 100,
	]),
]);


//门派绝招
mapping _family_uskills = ([
	"南海普陀山"		: ({ attack_spell("bighammer"),	powerup_spell("lianhua"), heal_spell("heal") }),
	"方寸山三星洞"	: ({ attack_perform("pili"), attack_spell("light"),	attack_spell("thunder")	}),
	"五庄观"			: ({ attack_spell("zhenhuo"), state_spell("qiankun"), attack_spell("zouxiao") }),
	"月宫"			: ({ state_spell("mihun"), state_spell("huimeng"), dot_spell("shiyue") }),

	"将军府"			: ({ attack_perform("sanban"), powerup_spell("jingxin"), attack_perform("huima") }),
	"阎罗地府"		: ({ attack_spell("gouhun"), powerup_spell("hell_pu"), dot_spell("inferno") }),
	"东海龙宫"		: ({ state_spell("fengbo"), powerup_spell("shield"), aoe_spell("roar") }),

	"大雪山"			: ({ attack_perform("chaofeng"), attack_spell("tuntian"), attack_spell("jieti") }),
	"陷空山无底洞"	: ({ state_spell("pozhan"), heal_spell("suliao"), attack_perform("qixiu") }),
	"火云洞"			: ({ aoe_spell("sanmei"), zhuang_spell(), yixing_spell() }),
	"盘丝洞"			: ({ state_spell("bone-fire"), attack_spell("love"), yihun_spell() }),
]);

//技能注解
mapping _skill_comment = ([
	"force"		: "内功修为",
	"spells"	: "法术修为",
	"dodge"		: "躲避攻击的能力",
	"parry"		: "格挡招架攻击的能力",
	"unarmed"	: "空手攻击能力",
]);

//随机选择一个门派，
string family_of_random()
{
	return random1(keys(_family_uskills));
}

//获取门派技能
mapping family_skills(string family)
{
	return _family_skills[family];
}

//获取门派绝技
mapping family_uskill(string family, int index)
{
	return _family_uskills[family][index];
}

//技能注解
string skill_comment(string skill)
{
	return or2(_skill_comment[skill], "");
}

