// by firefox 11/21/2009

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"yinshen2"
#define NAME			HIW"隐身"NOR
#define DURATION		120
#define CD				20
#define PROP			"env/invisibility"

int cast(object me)
{
	mapping buff_ori = BUFF->find(me, ID);

	if(buff_ori) {									//解除隐身
		BUFF->remove1(buff_ori);
		cd_start(me, ID, CD);
	}
	else if(cd_check(me, ID)) {						//隐身
		int skill = me->query_skill("buddhism", 1);
		int level = skill / 100;
		mapping req = ([
			"ex_value"	: ([ PROP				: "你已经在隐身中了。" ]),
			"skill1"	: ([ "buddhism"			: 100 ]),
			"prop"		: ([ "mana"				: skill ]),
		]);
		mapping buff = ([
			"id"		: ID,
			"name"		: NAME,
			"comment"	: "处于隐身状态，别人看不见你。",
			"duration"	: DURATION,
			"temp"		: ([ "no_heal_up/yinshen" : 1 ]),
			"replace"	: ([ PROP				: max2(1, level) ]),

			"start_msg"	: "$N喃喃地念了几句咒语。\n只见一道"HIW"白光"NOR"闪过，$N踪迹皆无。\n",
			"stop_msg"	: "\n"HIW"白光"NOR"闪过之后，$N又现出了身形。\n",
		]);
		if(!BTL->require(me, NAME, req)) return 1;
		BTL->pay(me, req["prop"]);
		BUFF->add(me, buff);
	}
	return 1;
}
