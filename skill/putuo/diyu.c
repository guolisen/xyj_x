
#include <xyj_x.h>
#include <ansi.h>

inherit SSERVER;


#define ID				"diyu"
#define NAME			HIY"我入地狱"NOR
#define CD				8

#define MSG0			HIY"$N口诵佛号，将%s"HIY"全力抛向空中！\n"NOR
#define MSG1			HIY"$N趁机步步紧逼，却不料%s"HIY"急速落下，正中顶门！\n"NOR
#define MSG1			HIY"$N退步防守，$n乘胜追击，却忽视了急速落下的%s"HIY"，正中顶门！\n"NOR


void hit_sb(object me, object victim, int damage, string msg, object weapon)
{
	msvx(msg, me, victim, part);
	victim->receive_damage("kee", damage, me);
	victim->receive_wound("kee", damage, me);
	COMBAT_D->report_status(victim); 
}


int perform(object me, object target)
{
	object weapon = me->query_temp("weapon");
	int cost = 100 + me->query("force_factor") * 2;
	int damage = cost;
	mapping req = ([
		"skill1"	: ([ "buddhism"	: 60, "lunhui-zhang" : 100 ]),
		"prop"		: ([ "force"		: cost ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ CEXP : 1, "sen" : 1, "max_sen" : -1, "cps" : 1, "int" : 1 ]),
		"skill"		: ([ "lotusforce" : 2 ]),
		"skill_pair": ([ ({"staff", "dodage"}) : 3 ]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("你要攻击谁？");
	if(!BTL->require(me, NAME, req)) return 1;
	if(!cd_start(me, ID, CD)) return notify_fail("你暂时还不能使用"NAME"。\n");
	BTL->pay(me, req["prop"]);

	msv(MSG0, me, target);

	if(BTL->cmp_random20(me, target, cmp_parm) > 90) {
		hit_sb(me, target, damage, MSG1, weapon);
	} else {
		hit_sb(target, me, damage / 3, MSG2, weapon);
	}
	return 1;
}
