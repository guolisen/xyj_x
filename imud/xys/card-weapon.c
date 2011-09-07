// by firefox 10/01/2010
// ����ɱ-����(�������ȶ̱����˺���1/3)

#include "xys.h"

mapping _weapons = ([
	
	"stick"		: ([
		({ "����𹿰�",	100,	2,	0 })			: 1,
		({ "�������˱�",	100,	2,	0 })			: 1,
		({ "�����",		66,		2,	0 })			: 10,
	]),

	"sword"		: ([
		({ "���ƽ�",		150,	1,	0 })			: 1,
		({ "������",		150,	1,	0 })			: 1,
		({ "��罣",		100,	1,	0 })			: 10,
	]),

	"whip"		: ([
		({ "�׹Ǳ�",		100,	2,	0 })			: 2,
		({ "������",		66,		2,	0 })			: 10,
	]),

	"hammer"	: ([
		({ "�Ű�ͭ��",	150,	1,	0 })			: 2,
		({ "�˰�÷����",	100,	1,	0 })			: 10,
	]),

	"spear"	: ([
		({ "�˱�����ǹ",	100,	2,	0 })			: 2,
		({ "�������е�",	66,		2,	0 })			: 10,
	]),

	"axe"	: ([
		({ "�Ű�ͭ��",	150,	1,	0 })			: 2,
		({ "�˰�÷����",	100,	1,	0 })			: 10,
	]),

	"blade"	: ([
		({ "������",		150,	1,	0 })			: 2,
		({ "���ϸ�",		100,	1,	0 })			: 10,
	]),

	"fork"	: ([
		({ "�Ź������",	100,	2,	0 })			: 2,
		({ "�ֲ�",		66,		2,	0 })			: 10,
	]),
	
	"staff"	: ([
		({ "�Ż�����",	150,	1,	0 })			: 2,
		({ "��ħ��",		100,	1,	0 })			: 10,
	]),
]);

//��ͨͽ�ֹ���
mapping _card_unarmed = ([

	"type"			: "����",
	"name"			: "ͽ��",
	"comment"		: "����ȥ��ȥץ�ɣ��ø�������ô�ɵ�",
	//��������
	"skill_type"	: "unarmed",
	EQU_PROP		: ([ "damage" : 100 ]),
	"slot"			: C_WEAPON,
	//����
	"fun"			: (: perform :),
	"success"		: 100,
	"dist"			: 1,
	"cd_prop"		: S_NO_MOVE,

	"cost_prop"		: "force",
	"cost"			: 10,
		
	"msg_start"		: CYN"$Ņ��һ����ȭ����$n���š�",
	"msg_ok"		: RED"$n���������������˸���������\n",
	"msg_fail"		: CYN"$n��������\n",
		
	"d_type"		: 1,
	"damage"		: 20,

]);

//��ͨ��������
mapping _card_weapon = ([

	"type"			: "����",
	//"name"			: "����",
	//"comment"		: "һ������",
	
	//��������
	//"skill_type"	: "stick",
	//EQU_PROP		: ([ "damage" : 60 ]),
	"slot"			: C_WEAPON,	
	
	//����
	"fun"			: (: perform :),
	"success"		: 100,
	//"dist"			: 2,
	"cd_prop"		: S_NO_MOVE,

	"cost_prop"		: "force",
	"cost"			: 15,
		
	"msg_start"		: CYN"$Nת���Ƶ�$n�������б�����Ȼ���֡�",
	"msg_ok"		: RED"$nһ���ҽУ����˲��ᣡ\n",
	"msg_fail"		: CYN"$nһ�����ɣ�$n�����漴��ա�\n",
		
	"d_type"		: 1,
	"damage"		: 30,

]);

//��ͨͽ�ֹ���
mapping _card_defense = ([

	"type"			: "����",
	"name"			: "����",
	"comment"		: "��ȡ����",

	"no_target"		: 1,
	"cost_prop"		: "force",
	"cost"			: -5,
		
	"msg_start"		: CYN"$N��ȡ���ƣ���������ű��˵ĵĹ�����\n",

]);


mapping aaa()
{
	int type = random1(keys(_weapons));
	mixed* m = roulette(_weapons[type]);

	mapping card = _card_weapon + ([
		"name"			: m[0],
		"comment"		: m[3],
		"dist"			: m[2],
		EQU_PROP		: ([ "damage" : m[1] ]),
	]);
	return card;
}
