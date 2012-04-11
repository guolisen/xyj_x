// by firefox 11/21/2009

#include <ansi.h>
#include <xyj_x.h>

#define ID				"grip"
#define NAME			HIY"观音手"NOR
#define CD				20
#define DURATION		6

#define MSG0			CYN"你暗暗向掌心催动内力和法力。\n"NOR
#define MSG1			HIY"$N法身暴长，巨大的手掌如同竹席一样向$n卷去！\n"NOR
#define MSG2			HIY"$n被$N一把捏在手心越差点攥出尿来，接着狠狠摔在地上！\n"NOR
#define MSG3			HIY"$n纵身而起，$N一把抓空。\n"NOR


int abort_attack(object me, object target)
{
	mapping buff = BUFF->find(me, ID);
	mapping cmp_parm = ([	//对方可用轻功躲闪，也可用法术抵抗
		"prop"		: ([ CEXP : 1, DEXP : 1, "sen" : 1, "max_sen" : -1 ]),
		"skill"		: ([ "dodge" : 2, "spells" : 2, "unarmed" : 2 ]),
		"temp"		: ([ "no_cast" : -1, "no_move" : -1 ]),
	]);
	if(me->is_busy()) return 0;
	if(buff) BUFF->remove1(buff);

	msv(MSG1, me, target);

	if(BTL->cmp_random20(me, target, cmp_parm) > thr) {
		BUFF->add(me, ([
			"id"		: ID,
			"name"		: NAME,
			"comment"	: "防御状态，时刻准备出手反击。",
			"duration"	: DURATION,
			"temp"		: ([ "No_Wield" : 1, "no_attack" : 1 ]),
			"_damage"	: mana + force,
			"_fun"		: (: abort_attack :),
		]));
		msv(MSG2, me, target);
		me->add("water", -40);
		me->receive_damage("kee", damage, attacker);
		//me->receive_wound("kee", damage/4, attacker);		

	} else {
		msv(MSG3, me, target);
	}
	BTL->fight_enemy(target, me);
	me->start_busy(1);
	if(!target->is_busy()) target->start_busy(1);
	return 1;
}



int perform(object me, object target)
{
	int mana = 10 + me->query("mana_factor");
	int force = 10 + me->query("force_factor");
	mapping req = ([
		"cd"		: ([ ID				: 1 ]),
		"skill1"	: ([ "buddhism"		: 140,	"jienan-zhi"	: 140 ]),
		"prop"		: ([ "mana"			: mana,	"force"			: force]),
	]);

	if(!BTL->require(me, NAME, req)) return 1;

	BTL->pay(me, req["prop"]);
	BUFF->start_cd(me, ID, NAME, CD);
	write(MSG0);
	BUFF->add(me, ([
		"id"		: ID,
		"name"		: NAME,
		"comment"	: "防御状态，时刻准备出手反击。",
		"duration"	: DURATION,
		"temp"		: ([ "No_Wield" : 1, "no_attack" : 1 ]),
		"_damage"	: mana + force,
		"_fun"		: (: abort_attack :),
	]));

	return 1;
}


