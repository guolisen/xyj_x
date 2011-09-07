// by firefox 10/01/2010
// 西游杀-门派绝技

#include "xys.h"

/********************************身份牌***********************************/

mapping _card_roles = ([
	
	ZHU				: ([
		"type"			: "身份",
		"name"			: "取经人",
		"comment"		: "被保护与被猎杀的对象，善于劝人向善",

		"add"			: ([ "kee" : 30 ]),
		"fun"			: (: cast :),
		"success"		: 120,
		"dist"			: 1,
		"cd_prop"		: S_NO_CAST,
		"cd"			: 4,
		"cost_prop"		: "mana",
		"cost"			: 30,
		
		"msg_start"		: CYN"$N对$n说道：做妖就象做人，要有仁慈的心，有了仁慈的心就是仁妖。",
		"msg_ok"		: HIY"$n腹中一紧，哗的一声，早午晚三餐喷涌而出！",
		"msg_fail"		: HIY"$n腹中一紧，连忙闭口，将即刻喷出的三餐强行咽下。",
		
		"damage_type"	: 2,	//精神伤害
		"damage"		: 30,
	]),

	ZHONG			: ([
		"type"			: "身份",
		"name"			: "徒弟",
		"comment"		: "保护取经人，舍生忘死",
	]),
	
	JIAN		: ([
		"type"		: "身份",
		"name"		: "假徒弟",
		"comment"	: "最后时刻，取经人",
	]),

	FAN			: ([
		"type"		: "身份",
		"name"		: "妖怪",
		"comment"	: "杀了取经人，午餐就有了",
	]),	
]);



