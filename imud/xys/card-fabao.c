// by firefox 10/01/2010
// 西游杀-法宝

#include "xys.h"

mapping _fabaos = ([	//movement damage dodage
	
	({ "金刚琢",		2,		10,		20,		"唐三藏的袈裟" })			: 1,
	({ "九头狮",		1,		15,		5,		"太乙救苦天尊的坐骑" })		: 3,
	({ "金毛犼",		1,		10,		5,		"观音菩萨的坐骑" })		: 4,
	
	({ 1,	"金刚琢",		"stick",	200,	2,	(: stick9 :),	([]) }),
	({ 1,	"幌金绳",		"whip",		10,		3,	(: whip8 :),	([]) }),
	({ 1,	"紫金葫芦",	"stick",	200,	2,	(: stick9 :),	([]) }),
	({ 10,	"羊脂玉净瓶",	"stick",	200,	2,	0,	([]) }),

]);

mapping aaa()
{
	mixed* m = roulette(_fabaos);

	mapping card = ([
		"type"			: "坐骑",
		"name"			: m[0],
		"comment"		: m[4],
		"slot"			: C_HORSE,
		EQU_PROP		: ([ "movement" : m[1], "damage" : m[2], "dodage" : m[3] ]),
	]);
	return card;
}


