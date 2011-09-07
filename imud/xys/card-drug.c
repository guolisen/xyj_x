// by firefox 10/01/2010
// 西游杀-药品

#include "xys.h"


mapping _drugs = ([
	// name			unit	kee		sen		force	mana
	({ "金创药",		"包",	30,		0,		0,		0 })	: 10,
	({ "混元丹",		"颗"	,	0,		30,		0,		0 })	: 10,
	({ "猕猴桃干",	"颗",	0,		0,		20,		20 })	: 10,
	({ "猕猴桃",		"颗",	0,		0,		40,		40 })	: 5,
	({ "九转还魂丹",	"颗",	100,	100,	0,		0 })	: 2,
	({ "野参果",		"颗",	100,	100,	100,	100 })	: 1,

]);

//随机选择一个
mapping select_one()
{
	mixed* m = roulette(_drugs);

	mapping card = ([
		"type"			: "药品",
		"name"			: m[0],
		"comment"		: 0,

		"no_target"		: 1,
		
		"msg_start"		: CYN"$N服下一" + m[1] + m[0] + "。\n"NOR,
		
		"add"			: ([ 
			"kee"			: m[2],
			"sen"			: m[3],
			"force"			: m[2],
			"mana"			: m[2], 
		]),
	]);

	return card;
}

