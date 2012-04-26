// firefox 04/12/2012
#include <ansi.h>
#include <xyj_x.h>

#define ID				"he"
#define NAME			HIY"观音纽"NOR
#define CD				10
#define DURATION		30

/*
那菩萨将杨柳枝儿，蘸了一点甘露洒将去，叫声『合！』
只见他丢了枪，一双手合掌当胸，再也不能开放，至今留了一个观音扭，即此意也。
*/
#define MSG0			HIY"$N对着$n轻轻一抬手，叫声『合！』...\n"NOR
#define MSG1			HIY"$n不由双手合掌当胸，再也不能开放！\n"NOR
#define MSG2			HIY"仿佛有股力量抓住$n，但被$n挣脱。\n"NOR
#define MSG3			CYN"$N猛一用力，双手终于分开了。\n"NOR

int cmd_filter(object me, string verb, string arg)
{
	string* verbs = ({"perform", "wield", "get", "drop", "give"});
	if(member_array(verb, verbs) != -1) {
		write("你双手不受控制！\n");
		return 1;
	}
	return 0;
}

int cast(object me, object target)
{
	int mana = 50 + me->query("mana_factor");
	mapping req = ([
		"skill1"	: ([ "buddhism"		: 120 ]),
		"prop"		: ([ "mana"			: mana ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ DEXP : 1, "mana_factor" : 1 ]),
		"skill"		: ([ "spells" : 3]),
		"temp"		: ([ "no_cast" : -1]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("你要对谁施放"NAME"？");
	if(!BTL->require(me, NAME, req)) return 1;
	if(!cd_start(me, ID, CD)) return notify_fail("你暂时还不能使用"NAME"。\n");

	BTL->pay(me, req["prop"]);

	msv(MSG0, me, target);
	
	if(BTL->cmp_random20(me, target, cmp_parm) > 125) {
		object weapon, env = environment(target);
		while(weapon = me->query_temp("weapon")) {
			weapon->unequip();
			if(env) weapon->move(env);
		}
		BUFF->add(target, ([
			"id"		: ID,
			"name"		: NAME,
			"comment"	: "双手合掌当胸，不能开放。",
			"class"		: "控制术",
			"duration"	: DURATION,
			"add_temp"	: ([
				"no_attack"		: 1,
				"no_wield"		: 1,
				"cmd_filter/*"	: ({ (: cmd_filter :) }),
			]),
			"stop_msg"	: MSG3,
		]));
	} else {
		msv(MSG2, me, target);
	}
	BTL->fight_enemy(target, me);
	return 1;
}
