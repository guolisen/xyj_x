// by firefox 10/01/2010
// ����ɱ-ҩƷ

#include "xys.h"


mapping _drugs = ([
	// name			unit	kee		sen		force	mana
	({ "��ҩ",		"��",	30,		0,		0,		0 })	: 10,
	({ "��Ԫ��",		"��"	,	0,		30,		0,		0 })	: 10,
	({ "⨺��Ҹ�",	"��",	0,		0,		20,		20 })	: 10,
	({ "⨺���",		"��",	0,		0,		40,		40 })	: 5,
	({ "��ת���굤",	"��",	100,	100,	0,		0 })	: 2,
	({ "Ұ�ι�",		"��",	100,	100,	100,	100 })	: 1,

]);

//���ѡ��һ��
mapping select_one()
{
	mixed* m = roulette(_drugs);

	mapping card = ([
		"type"			: "ҩƷ",
		"name"			: m[0],
		"comment"		: 0,

		"no_target"		: 1,
		
		"msg_start"		: CYN"$N����һ" + m[1] + m[0] + "��\n"NOR,
		
		"add"			: ([ 
			"kee"			: m[2],
			"sen"			: m[3],
			"force"			: m[2],
			"mana"			: m[2], 
		]),
	]);

	return card;
}

