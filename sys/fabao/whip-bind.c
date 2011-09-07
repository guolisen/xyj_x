// by firefox 11/21/2009

/*
法宝——捆绑鞭

- 武器鞭
- 捆绑对手

剧本

牛魔王：今日边个够胆挡我嘅，我就杀边个。
白晶晶：领教我嘅白骨鞭啦！

*/

#include <weapon.h>
#include <ansi.h>

inherit WHIP;

void create()
{
	set_name("捆绑鞭", ({"whip"}));
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
	}
	init_whip(5);
	setup();
}

#define CD_ID				"bind"

void init_var()
{
	_subs = ([
		"龙骨鞭"			: ([
			"ids"			: ({"longgu bian", "bian", "whip"}),
			"long"			: "一条白森森的龙骨，透着死亡的气息。",
			"color"			: HIW,
			"unit"			: "条",
		]),
		"软龙筋"			: ([
			"ids"			: ({"ruanlong jin", "jin", "whip"}),
			"long"			: "一根柔软坚韧的龙筋。",
			"color"			: 0,
			"unit"			: "根",
		]),
	]);

	
	//特征，法术/内功，
	_trais = ([
		//初始属性
		"prop"	: ([			
			"personality"	: -1,
		]),

		//根据百分比加成的属性
		"prop_x"	: ([
			"spells"		: 10,
			"damage"		: 40,
		]),
	]);

	_act = ([
		"exp_x"			: 50,					//50%的经验分配给祭出功能

		"cd_id"			: CD_ID,				//共CD的ID，多种法宝可能共CD
		"cd"			: 30,

		"target"		: ([ "need_enemy" : 1, "need_living" : 1 ]),

		"req"			: ([
			"cd"			: ([ CD_ID			: 1 ]),
			"skill1"		: ([ "spells"		: 100]),
			"prop"			: ([ "mana"			: 100,	"sen"	: 20 ]),
		]),
		"cmp"			: ([
			"prop"			: ([ "sen" : 1, "max_sen" : -1, "mana_factor" : 1, DEXP : 1 ]),
			"temp"			: ([ "no_cast" : -2 ]),
			"skill"			: ([ "spells" : 2]),
		]),
		"threshold"		: 60,
		"msg_start"		: "$N念动咒语，手中%s腾空而起，向$n飞去。",
		"msg_success"	: "%s如一条巨蟒，将$n缠了个结结实实。",
		"msg_fail"		: "$n催动法力相抗，%s近身不得又飞回$N手中。",
	]);
}

//法宝命中
int ji_success(object who, object target, int fabao_exp)
{
	//捆绑


}
