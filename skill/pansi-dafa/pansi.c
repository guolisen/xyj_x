// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <ansi.h>
#include <xyj_x.h>

#define ID				"pansi"
#define NAME			HIB"神龙盘丝"NOR
#define DURATION		8
#define CD				20

#define MSG0			HIW"$N念动咒语，突然飞出一张网，向$n当头罩去！\n"NOR
#define MSG1			HIW"$n猝不及防，被网粘在原地动弹不得。\n"NOR
#define MSG2			"$n急退数丈，一网落空。\n"NOR
#define MSG3			"$n张开血盆大口，将网一口吞下！\n"NOR

/*
神龙盘丝
春卅娘：神龙盘丝。
牛魔王：雕虫小技。(一口吞下)
*/

void po_lost(object target, int n);

int cast(object me, object target)
{
	int thr = 100;
	mapping req = ([
		"cd"		: ([ ID				: 1 ]),
		"skill1"	: ([ "pansi-dafa"	: 30 ]),
		"prop"		: ([ "mana"			: 50 ]),
	]);
	mapping cmp_parm = ([	//对方可用轻功躲闪，也可用法术抵抗
		"prop"		: ([ "str" : -2, CEXP : 1, DEXP : 1, "sen" : 1, "max_sen" : -1 ]),
		"skill"		: ([ "dodge" : 2, "spells" : 2 ]),
		"temp"		: ([ "no_cast" : -1, "no_move" : -1, "chaofeng_busy" : -1, "fc_pfm_busy" : -1 ]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("你要网谁？");
	
	if(!BTL->require(me, NAME, req)) return 1;

	BTL->pay(me, req["prop"]);
	BUFF->start_cd(me, ID, NAME, CD);

	msv(MSG0, me, target);

	if(target->is_busy()) thr -= 20;

	if(BTL->cmp_random20(me, target, cmp_parm) > thr) {
		mixed n = target->query_busy();
		n = intp(n) ? max2(n, DURATION) : DURATION;		//可以覆盖目标的忙状态
		target->start_busy(n);
		msv(MSG1, me, target);

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
