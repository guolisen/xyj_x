// by firefox 10/01/2010
// ����ɱ-����

#include "uskill.c"

//���ɼ���
mapping _family_skills = ([

	"�Ϻ�����ɽ"	: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"staff"		: 100,	
	]),
	"����ɽ���Ƕ�"	: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"sword"		: 100,	"stick"		: 100,
	]),
	"��ׯ��"		: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"sword"		: 100,	"hammer"	: 100,	"blade"		: 100,
	]),
	"�¹�"		: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 120,	"parry"		: 100,
		"unarmed"	: 80,	"sword"		: 100,	"whip"		: 100,
	]),

	"������"		: ([
		"force"		: 100,	"spells"	: 80,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"mace"		: 120,	"axe"		: 120,	"spear"		: 120,		
	]),
	"���޵ظ�"	: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"sword"		: 100,	"stick"		: 100,	"whip"		: 100,		
	]),
	"��������"	: ([
		"force"		: 100,	"spells"	: 75,	"dodge"		: 75,	"parry"		: 100,
		"unarmed"	: 150,	"hammer"	: 100,	"fork"		: 100,
	]),
	"��ѩɽ"		: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"sword"		: 100,	"blade"		: 100,
	]),
	"�ݿ�ɽ�޵׶�"	: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"sword"		: 100,	"blade"		: 100,
	]),
	"���ƶ�"		: ([
		"force"		: 100,	"spells"	: 100,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 100,	"stick"		: 100,	"fork"		: 100,	"spear"		: 100,
	]),
	"��˿��"		: ([
		"force"		: 100,	"spells"	: 120,	"dodge"		: 100,	"parry"		: 100,
		"unarmed"	: 80,	"sword"		: 100,	"whip"		: 100,
	]),
]);


//���ɾ���
mapping _family_uskills = ([
	"�Ϻ�����ɽ"		: ({ attack_spell("bighammer"),	powerup_spell("lianhua"), heal_spell("heal") }),
	"����ɽ���Ƕ�"	: ({ attack_perform("pili"), attack_spell("light"),	attack_spell("thunder")	}),
	"��ׯ��"			: ({ attack_spell("zhenhuo"), state_spell("qiankun"), attack_spell("zouxiao") }),
	"�¹�"			: ({ state_spell("mihun"), state_spell("huimeng"), dot_spell("shiyue") }),

	"������"			: ({ attack_perform("sanban"), powerup_spell("jingxin"), attack_perform("huima") }),
	"���޵ظ�"		: ({ attack_spell("gouhun"), powerup_spell("hell_pu"), dot_spell("inferno") }),
	"��������"		: ({ state_spell("fengbo"), powerup_spell("shield"), aoe_spell("roar") }),

	"��ѩɽ"			: ({ attack_perform("chaofeng"), attack_spell("tuntian"), attack_spell("jieti") }),
	"�ݿ�ɽ�޵׶�"	: ({ state_spell("pozhan"), heal_spell("suliao"), attack_perform("qixiu") }),
	"���ƶ�"			: ({ aoe_spell("sanmei"), zhuang_spell(), yixing_spell() }),
	"��˿��"			: ({ state_spell("bone-fire"), attack_spell("love"), yihun_spell() }),
]);

//����ע��
mapping _skill_comment = ([
	"force"		: "�ڹ���Ϊ",
	"spells"	: "������Ϊ",
	"dodge"		: "��ܹ���������",
	"parry"		: "���мܹ���������",
	"unarmed"	: "���ֹ�������",
]);

//���ѡ��һ�����ɣ�
string family_of_random()
{
	return random1(keys(_family_uskills));
}

//��ȡ���ɼ���
mapping family_skills(string family)
{
	return _family_skills[family];
}

//��ȡ���ɾ���
mapping family_uskill(string family, int index)
{
	return _family_uskills[family][index];
}

//����ע��
string skill_comment(string skill)
{
	return or2(_skill_comment[skill], "");
}

