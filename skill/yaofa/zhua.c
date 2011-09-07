// by firefox 11/21/2009


#include <xyj_x.h>
#include <ansi.h>

#define ID				"zhua"
#define NAME			HIW"利爪"NOR
#define CD				20
#define DUATION			6
#define DAMAGE_MUTI		7


mixed* word_list  = ({
	({HIY"暖流"NOR, "玉树临风", "大手", "脸红心跳", "又羞又恼"}),
	({HIM"暖香"NOR, "吐气如兰", "玉手", "浑身酥软", "手足无措"}),
});

mapping tab = ([
	"attack"	: "$n感到一阵%s袭来，原来是$N%s站在身后，%s搭在$n背上，\n轻抚向$n头顶。",
	"success"	: "$n不由%s。谁料%s变"NAME"，悄然抓下...\n",
	"failure"	: "$n%s，闪身躲开。\n",
]);

int cast(object me, object target)
{
	int skill = me->query_skill("yinfeng-zhua", 1);
	int force = 100 + 2 * me->query("force_factor");
	string w, msg;
	mapping req = ([
		"cd"		: ([ ID			: 1 ]),
		"skill1"	: ([ "yaofa"	: 150,	"yinfeng-zhua"	: 150 ]),
		"prop"		: ([ "mana"		: 50,	"force"			: force ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ "per" : 3, "int" : 2, "mana" : 1, "daoxing" : 1, "str" : -3]),
		"skill"		: ([ "spells" : 2]),
	]);
	
	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("抓谁？\n");
	if(me->query_per() < 20) return notify_ok("你太丑了，别去吓人了。\n");	
	if(me->is_fighting() || target->is_fighting())
		return notify_ok("打架中不能偷袭。\n");

	if(!BTL->require(me, NAME, req)) return 1;
	BTL->pay(me, req["prop"]);
	w = me->query("gender") == "男性" ? word_list[0] : word_list[1];
	msg = sprintf(tab["attack"], w[0], w[1], w[2]);
	
	BUFF->start_cd(me, ID, NAME, CD);
	if(BTL->random_cmp(me, target, cmp_parm) >= 60) {
		int damage;		
		BUFF->start_claw(me, DUATION, skill/3, "$N的"HIW"爪子"NOR"收了回去。");

		damage = me->query_str() + me->query_temp("apply/damage");
		damage = MATH->random_pct(damage, 30) * DAMAGE_MUTI;
		trace("zhua damage:" + damage);
		target->receive_damage("kee", damage, me);
		target->receive_wound("kee", damage, me);
		
		msg += sprintf(tab["success"], w[3], w[2]);
		msv(msg, me, target);
		COMBAT_D->report_status(target, 1);
		BTL->fight_enemy(target, me);
		
	} else {
		msg += sprintf(tab["failure"], w[4]);
		msv(msg, me, target);
	}
	if(!target->is_busy()) target->start_busy(1);
	me->start_busy(1);
	return 1;
}
