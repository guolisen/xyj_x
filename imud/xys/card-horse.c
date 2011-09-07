// by firefox 10/01/2010
// 西游杀-马匹

#include "xys.h"


mapping _horses = ([	//movement damage dodage
	
	({ "金翅大鹏",	2,		10,		20,		"唐三藏的袈裟" })			: 1,
	({ "九头狮",		1,		15,		5,		"太乙救苦天尊的坐骑" })		: 3,
	({ "金毛犼",		1,		10,		5,		"观音菩萨的坐骑" })		: 4,

	({ "青牛",		0,		15,		0,		"太上老君的坐骑" })		: 10,
	({ "白龙马",		1,		5,		10,		"唐三藏的袈裟" })			: 10,

	({ "黄骠透骨龙",	1,		0,		20,		"秦叔宝的坐骑" })			: 15,
	({ "铁脚枣骝驹",	1,		0,		15,		"程咬金的坐骑" })			: 15,

	({ "小毛驴",		0,		0,		20,		"温顺的小毛驴" })			: 15,
	({ "老牛",		0,		5,		0,		"迟缓的老牛" })			: 15,
]);


mapping aaa()
{
	mixed* m = roulette(_horses);

	mapping card = ([
		"type"			: "坐骑",
		"name"			: m[0],
		"comment"		: m[4],
		"slot"			: C_HORSE,
		EQU_PROP		: ([ "movement" : m[1], "damage" : m[2], "dodage" : m[3] ]),
	]);
	return card;
}


