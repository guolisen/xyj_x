// firefox 11/21/2009

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define ID			"wuxue"
#define NAME		HIW"舞雪"NOR
#define DURATION	60
#define CD			70

int perform(object me, object target)
{
	mapping buff_ori = BUFF->find(me, ID);	

	if(buff_ori) {
		BUFF->remove1(buff_ori);
	} 	
	else if(cd_check(me, ID)) {
		int enhance = me->query_skill("dodge") * 40 / (20 + me->query("str"));	//与体重成反比
		mapping req = ([
			"ex_temp"	: ([ "powerup"		: "你已经在运功中了。" ]),
			"skill_map"	: ([ "dodge"		: "moondance",	"force"		: "moonforce" ]),
			"skill"		: ([ "dodge"		: 100,			"sword"		: 100,		 "force"	: 100 ]),
			"prop"		: ([ "force"		: 50 ]),
		]);
		mapping buff = ([
			"id"		: ID,
			"name"		: NAME,
			"comment"	: "施展舞雪，轻功提高。",
			"duration"	: DURATION,
			"temp"		: ([ "powerup" : 1 ]),
			"add_apply"	: ([
				"attack"	: -enhance,
				"dodge"		: enhance,
			]),
			"start_msg"	: HIW"$N略一提气，运起轻功，拔剑起舞。只见$N足不沾地，手中剑越舞越快，逐渐幻做一团白雾，满堂滚动。",
			"stop_msg"	: HIW"$N放慢脚步，放缓剑招。",
		]);
		if(!BTL->require(me, NAME, req)) return 1;
		if(!cd_start(me, ID, CD)) return notify_fail("你暂时还不能使用"NAME"。\n");
		BTL->pay(me, req["prop"]);
		BUFF->add(me, buff);
	}
	return 1;
}
