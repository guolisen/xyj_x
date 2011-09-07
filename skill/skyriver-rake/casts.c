// by firefox 02/09/2010

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"fireback"
#define NAME			HIW"法术反弹"NOR
#define CD				30


mapping* casts = ({
	([
		"name"		: "自焚真火",
		"msg"		: HIC
			"$N几个指头迅速捻动，突然张嘴一喷！红橙黄三道火焰呼！地一声向$n卷去！\n"
			"但是火焰被$n以法力一逼，反向$N回卷而去！\n"
			"结果自焚真火反噬，$N被烧焦了！\n",
		"prefix"	: "烤焦的",
	]),
	([
		"name"		: "大力弹簧杵",
		"msg"		: HIC
			"$N口中念了几句咒文，半空中现出阿傩，迦叶二尊者，各人手执\n一根巨大无比的弹簧杵，呼！地一声向$n当头砸下！\n"
			"但是弹簧杵被$n以法力一引，反而砸到了$N的顶门！\n"
			"结果砸个正着，$N被砸得满头是包！\n",
		"prefix"	: "满头包的",
	])
});


int perform(object me, object target)
{
	mapping req = ([
		"cd"		: ([ ID					: 1 ]),
		"skill1"	: ([ "skyriver-rake"	: 250 ]),
		"ex_class"	: ([ "变身术" : 1 ]),
		"prop"		: ([ "force"			: 10 ]),
	]);
	mapping cast = random1(casts);
	mapping buff = ([
		"id"		: ID,
		"name"		: NAME,
		"comment"	: "被法术砸变样了。",
		"class"		: "变身术",
		"duration"	: CD - 5,
		"temp"		: ([
			"apply/name"	: ({ cast["prefix"] + me->name() }),

		]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("打谁？\n");
	if(!BTL->require(me, NAME, req)) return 1;
	BTL->pay(me, req["prop"]);
	
	BTL->start_cd(me, ID, NAME, CD);

	BUFF->add(me, buff);
	message_vision(cast["msg"] + NOR, me, target);

	me->receive_wound("kee", 500, me);
	me->receive_wound("sen", 500, me);
	COMBAT_D->report_status(me);
	COMBAT_D->report_sen_status(me);

	BTL->fight_enemy(target, me);
	me->start_busy(1);
	return 1;
}
