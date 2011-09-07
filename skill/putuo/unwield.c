// by firefox  06/22/2009

inherit F_CLEAN_UP;

#include <ansi.h>
#include <xyj_x.h>

#define ID				"unwield"
#define NAME			HIY"放下屠刀"NOR
#define DURATION		30
#define CD				10

#define MSG0				"对方已经放下屠刀了。"

int cast(object me, object target)
{
	int skill = me->query_skill("buddhism", 1);
	mapping req = ([
		"cd"		: ([ ID			: 1 ]),
		"ex_temp"	: ([ "No_Wield"	: MSG0]),
		"skill1"	: ([ "buddhism"	: 250 ]),
		"prop"		: ([ "mana"		: skill ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ "mana"		: 2,	"daoxing"	: 2 ]),
		"skill"		: ([ "spells"	: 4 ]),
	]);
	
	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("要劝谁放下屠刀？");
	if(!target->query_temp("weapon")) return notify_ok(MSG0 + "\n");
	if(!BTL->require(me, NAME, req)) return 1;
	BTL->pay(me, req["prop"]);
	BUFF->start_cd(me, ID, NAME, CD);

	message_vision(
		"突然佛光万道，瑞气千条，$N闭目合十，朗声念道：\n\n"HIY
		"    苦海无边，回头是岸；放下屠刀，立地成佛。\n\n" NOR, me);

	if(BTL->random_pct(BTL->cmp_parm(me, target, cmp_parm), 30) >= 40) {
		BUFF->start_no_wield(me, DURATION, HIY"$N身后的佛光渐渐隐去。\n");
		BUFF->start_no_wield(target, DURATION);
		message_vision("$N自知罪孽深重，顿觉手中兵刃有如千金重，再也举不起来。\n\n", target);
	} else {
		message_vision("$n对$N的话充耳不闻，不为所动。\n\n", me, target);
	}
	me->start_busy(1);

	return 1;
}
