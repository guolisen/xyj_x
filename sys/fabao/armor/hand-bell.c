// by firefox 11/21/2009

/*
法宝——手铃

- 手链
- 跳舞铃铛

剧本

紫霞用银索金玲让杨戬和四大天王跳舞，然后逃脱。

*/
#include <armor.h>
#include "_base.h"

inherit HANDS;

void create()
{
	set_name("手铃", ({"hand bell"}));
	set_weight(80);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "steel");
	}
	setup();
}

#define CD_ID				"dance"

void init_var()
{
	_subs = ([
		"银索金玲"			: ([
			"ids"			: ({"yinsuo jinling", "jinling", "ling", "bell"}),
			"long"			: "一串用银线串起的金玲。",
			"color"			: HIY,
			"unit"			: "串",
		]),
		"金索银玲"			: ([
			"ids"			: ({"jinsuo yinling", "yinling", "ling", "bell"}),
			"long"			: "一串用金线串起的银玲。",
			"color"			: WHT,
			"unit"			: "串",
		]),
	]);

	
	//特征，法术/内功，
	_trais = ([
		//盔甲
		"prop"	: ([			
			"personality"	: 1,
		]),

		//按百分比加成的属性
		"prop_x"	: ([
			"armor"			: 10,
			"spells"		: 50,
		]),

		"prop_x"	: ([
			"damage"		: 10,		//1M 5点？
		]),

		"eff_x"			: 50,	//特效所占比例
		
		"on_wound"		: (: on_wound :),

	]);

	_act = ([
		"exp_x"			: 50,					//50%的经验分配给法宝

		"cd_id"			: CD_ID,				//共CD的ID，多种法宝可能共CD
		"cd"			: 30,

		"target"		: ([ "need_enemies" : 1, "need_living" : 1 ]),

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
		"msg_start"		: "$N摇动手上的%s，轻快悦耳的铃声传播开来。",
		"msg_success"	: "$n被铃声感染，笑逐颜开，随着铃声载歌载舞。",
		"msg_fail"		: 0,
	]);
}

//受到伤害
void on_wound(object owner, object attacker)
{
}

//法宝命中
int ji_success(object who, object target, int fabao_exp)
{
	//不能出招，不能动，不能kill，受到就醒攻击


}
