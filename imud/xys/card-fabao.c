// by firefox 10/01/2010
// ����ɱ-����

#include "xys.h"

mapping _fabaos = ([	//movement damage dodage
	
	({ "�����",		2,		10,		20,		"�����ص�����" })			: 1,
	({ "��ͷʨ",		1,		15,		5,		"̫�Ҿȿ����������" })		: 3,
	({ "��ë��",		1,		10,		5,		"��������������" })		: 4,
	
	({ 1,	"�����",		"stick",	200,	2,	(: stick9 :),	([]) }),
	({ 1,	"�Ͻ���",		"whip",		10,		3,	(: whip8 :),	([]) }),
	({ 1,	"�Ͻ��«",	"stick",	200,	2,	(: stick9 :),	([]) }),
	({ 10,	"��֬��ƿ",	"stick",	200,	2,	0,	([]) }),

]);

mapping aaa()
{
	mixed* m = roulette(_fabaos);

	mapping card = ([
		"type"			: "����",
		"name"			: m[0],
		"comment"		: m[4],
		"slot"			: C_HORSE,
		EQU_PROP		: ([ "movement" : m[1], "damage" : m[2], "dodage" : m[3] ]),
	]);
	return card;
}


