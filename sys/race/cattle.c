// by firefox 06/21/2010

#include "race-base.h"

string _long = @LONG

一头牛，头如峻岭，眼若闪光，两只角似两座铁塔，牙排利刃。
连头至尾，有千余丈长短，自蹄至背，有八百丈高下。

LONG;

void init_var()
{
	//物种子类以及名称
	_subs = ([
		"白牛"			: ([
			"ids"			: ({"bai niu", "niu", "cattle"}),
			"long"			: _long,
			"color"			: HIW,
			"unit"			: "头",
		]),
		"青牛"			: ([
			"ids"			: ({"qing niu", "niu", "cattle"}),
			"long"			: _long,
			"color"			: HIC,
			"unit"			: "头",
		]),
	]);

	//真身特征
	_traits = ([
		"limbs"			: CATTLE_LIMBS,

		"kee"			: 400,					//气血增量
		"sen"			: 0,					//精神增量

		//直接加成属性
		"add_apply"		: ([
			"personality"	: -30,
		]),
		
		//按百分比加成的属性
		"add_apply_x"		: ([
			"armor"			: 100,
			"strength"		: 30,
			"parry"			: 0,				//忘记招架吧
			"dodge"			: 0,				//体型太大，难闪转腾挪
		]),

		"skill_bonus"	: ([					//技能加成，最终会增加到apply上
			"moyun-shou"	: 10,
			"moshenbu"		: 10,
			"huomoforce"	: 10,
			"pingtian-dafa"	: 20,
		]),
	]);
	
	//武器
	_weapons = ({ "horn", "hoof", "tail"});

	//出生信息
	_born = ([
		"place"		: "/d/gao/daotian1",
		"sb."		: "/d/gao/npc/bull",
		"msg"		: "$N扑通一声掉在地上，醒了过来。\n" + CYN + MSG_LICK,
	]);
}


#define CURE_RATIO		300

mapping _act_tab = ([
	"hand"		: "扳",			"axe"		: "劈",
	"blade"		: "砍",			"sword"		: "削",
	"dagger"	: "割",			"fork"		: "叉",
	"hammer"	: "砸",			"spear"		: "挑",
	"staff"		: "扫",			"stick"		: "扫",
	"throwing"	: "射",			"whip"		: "抽",
	"mace"		: "抽",
]);

string _msg = CYN"\n$n大叫一声将$N的头%s了下来。\n"
	+ "$N腔里又钻出一个牛头来，口吐黑气，眼放金光！\n"NOR;

//施展绝技
int unique_skill(object me, object target)
{
	int eff_kee = me->query("eff_kee");
	int max_kee = me->query("max_kee");
	int cure = me->query_skill("spells") * CURE_RATIO / 100;
	
	if(eff_kee > max_kee/3) return notify_fail("没人打爆你的头，不用再生。\n");
	else {
		object enemy = BTL->random_enemy(me);
		object weapon = enemy->query_temp("weapon");
		string act = "扳";
		if(weapon) act = or2(_act_tab[weapon->query("skill_type")], act);

		MSG->vision(_msg, me, enemy, act);

		me->add("mana", cure/10);
		me->receive_curing("kee", cure);
		me->receive_heal("kee", cure);
		new("/d/qujing/jilei/obj/head")->move(environment(me));
	}
	return 0;
}

