// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <ansi.h>
#include <xyj_x.h>

#define ID				"grip"
#define NAME			HIY"观音手"NOR
#define CD				20

#define MSG0			CYN"你暗暗向掌心催动内力和法力。\n"NOR
#define MSG1			HIY"$N法身暴长，巨大的手掌如同竹席一样向$n卷去！\n"NOR
#define MSG2			HIY"$n被$N一把捏在手心越差点攥出尿来，接着狠狠摔在地上！\n"NOR
#define MSG3			HIY"$n纵身而起，$N一把抓空。\n"NOR




void po_lost(object target, int n);

int cast(object me, object target)
{
	int thr = 100;
	int mana = 10 + me->query("mana_factor");
	int force = 10 + me->query("force_factor");
	mapping req = ([
		"cd"		: ([ ID				: 1 ]),
		"skill1"	: ([ "buddhism"		: 140,	"jienan-zhi"	: 140 ]),
		"prop"		: ([ "mana"			: mana,	"force"			: force]),
	]);
	mapping cmp_parm = ([	//对方可用轻功躲闪，也可用法术抵抗
		"prop"		: ([ CEXP : 1, DEXP : 1, "sen" : 1, "max_sen" : -1 ]),
		"skill"		: ([ "dodge" : 2, "spells" : 2, "unarmed" : 2 ]),
		"temp"		: ([ "no_cast" : -1, "no_move" : -1 ]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("你要网谁？");
	
	if(!BTL->require(me, NAME, req)) return 1;

	BTL->pay(me, req["prop"]);
	BUFF->start_cd(me, ID, NAME, CD);

	write(MSG0);

			mapping buff = ([
			"id"		: ID,
			"name"		: NAME,
			"comment"	: "防御状态，时刻准备出手反击。",
			"duration"	: DURATION,
			"temp"		: ([ "no_cast" : 1 ]),

			"start_msg"	: MS1,
		]);
		BUFF->add(me, buff);


	if(target->is_busy()) thr -= 20;

	if(BTL->cmp_random20(me, target, cmp_parm) > thr) {

	} else {
		msv(MSG3, me, target);

		SKILL_D("pansi-dafa")->random_level_up(me);
	} else {
		string msg = (target->query_per() > 18) ? MSG2 : MSG3;
		msv(msg, me, target);
		if(!userp(target) && !random(10)) 
			target->command("say 雕虫小技！");
	}
	BTL->fight_enemy(target, me);
	me->start_busy(1);
	return 1;
}


