// by firefox 10/01/2010
// 西游杀-武器(长兵器比短兵器伤害低1/3)

#include "xys.h"

mapping _weapons = ([
	
	"stick"		: ([
		({ "如意金箍棒",	100,	2,	0 })			: 1,
		({ "随心铁杆兵",	100,	2,	0 })			: 1,
		({ "蟠龙棍",		66,		2,	0 })			: 10,
	]),

	"sword"		: ([
		({ "青云剑",		150,	1,	0 })			: 1,
		({ "楚妃剑",		150,	1,	0 })			: 1,
		({ "青虹剑",		100,	1,	0 })			: 10,
	]),

	"whip"		: ([
		({ "白骨鞭",		100,	2,	0 })			: 2,
		({ "软龙筋",		66,		2,	0 })			: 10,
	]),

	"hammer"	: ([
		({ "九瓣铜锤",	150,	1,	0 })			: 2,
		({ "八瓣梅花锤",	100,	1,	0 })			: 10,
	]),

	"spear"	: ([
		({ "八宝驼龙枪",	100,	2,	0 })			: 2,
		({ "三尖两刃刀",	66,		2,	0 })			: 10,
	]),

	"axe"	: ([
		({ "九瓣铜锤",	150,	1,	0 })			: 2,
		({ "八瓣梅花锤",	100,	1,	0 })			: 10,
	]),

	"blade"	: ([
		({ "宣花斧",		150,	1,	0 })			: 2,
		({ "开上斧",		100,	1,	0 })			: 10,
	]),

	"fork"	: ([
		({ "九股托天叉",	100,	2,	0 })			: 2,
		({ "钢叉",		66,		2,	0 })			: 10,
	]),
	
	"staff"	: ([
		({ "九环锡杖",	150,	1,	0 })			: 2,
		({ "降魔杖",		100,	1,	0 })			: 10,
	]),
]);

//普通徒手攻击
mapping _card_unarmed = ([

	"type"			: "武器",
	"name"			: "徒手",
	"comment"		: "扑上去上去抓吧，泼妇都是这么干的",
	//武器属性
	"skill_type"	: "unarmed",
	EQU_PROP		: ([ "damage" : 100 ]),
	"slot"			: C_WEAPON,
	//技能
	"fun"			: (: perform :),
	"success"		: 100,
	"dist"			: 1,
	"cd_prop"		: S_NO_MOVE,

	"cost_prop"		: "force",
	"cost"			: 10,
		
	"msg_start"		: CYN"$N抬手一记重拳打向$n面门。",
	"msg_ok"		: RED"$n躲闪不及，被打了个满脸花！\n",
	"msg_fail"		: CYN"$n闪身躲过。\n",
		
	"d_type"		: 1,
	"damage"		: 20,

]);

//普通武器攻击
mapping _card_weapon = ([

	"type"			: "武器",
	//"name"			: "长剑",
	//"comment"		: "一柄长剑",
	
	//武器属性
	//"skill_type"	: "stick",
	//EQU_PROP		: ([ "damage" : 60 ]),
	"slot"			: C_WEAPON,	
	
	//技能
	"fun"			: (: perform :),
	"success"		: 100,
	//"dist"			: 2,
	"cd_prop"		: S_NO_MOVE,

	"cost_prop"		: "force",
	"cost"			: 15,
		
	"msg_start"		: CYN"$N转身绕道$n背后，手中兵器悄然出手。",
	"msg_ok"		: RED"$n一声惨叫，受伤不轻！\n",
	"msg_fail"		: CYN"$n一纵数丈，$n攻势随即落空。\n",
		
	"d_type"		: 1,
	"damage"		: 30,

]);

//普通徒手攻击
mapping _card_defense = ([

	"type"			: "武术",
	"name"			: "防守",
	"comment"		: "采取守势",

	"no_target"		: 1,
	"cost_prop"		: "force",
	"cost"			: -5,
		
	"msg_start"		: CYN"$N采取守势，认真提防着别人的的攻击。\n",

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
