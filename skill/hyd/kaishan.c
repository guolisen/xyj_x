// by pkyou@xyj

//西游记不宜过度突出内力这个概念，pkyou的原创被我改的面目全非了。
//重新定位：突出大力。力量压制，让对方受内伤，并且无力招架后继进攻

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"kaishan"
#define NAME			HIR"五丁开山"NOR
#define CD				20
#define DURATION		10

int perform(object me, object target)
{
	int enhance = me->query_skill("huomoforce", 1) / 2;
	int stick = me->query_skill("dali-bang", 1);

	mapping req = ([
		"skill1"	: ([ "stick"	: 100 ]),
		"prop"		: ([ "force"	: stick ]),
	]);

	mapping buff = ([
		"id"		: ID,
		"name"		: NAME,
		"comment"	: "浑身充满力量。",
		"duration"	: DURATION,
		"add_apply" : ([ "strength" : enhance ]),	//爆发力
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("砸谁？\n");
	if(!me->is_fighting(target)) return notify_ok("「"NAME"」只能在战斗中使用。\n");

	if(!BTL->require(me, NAME, req)) return 1;
	if(!cd_start(me, ID, CD)) return notify_ok("你暂时不能使用「"NAME"」！\n");

	BTL->pay(me, req["prop"]);

	BUFF->add(me, buff);		//增加力量buff

	msv(HIC"\n$N大喝一声身形暴涨，如同五丁力士一般，举起手中兵器连续砸向$n！\n", me, target);
	
	trace("me str:" + me->query_str() + " target str:" + target->query_str());
	//角力，力亏者受伤
	if(enhance + me->query_str() > 3 * random(target->query_str())) {
		
		mapping debuff = ([
			"id"		: ID + "ed",
			"name"		: HIR"无力招架"NOR,
			"comment"	: "被人砸脱力，无法再招架了。",
			"duration"	: DURATION,
			"add_apply" : ([ "parry" : -stick * 2 ]),	//招架算是废了
		]);
		int damage = me->query_str() - target->query_str();
		damage = max2(damage * 4, 50);

		target->receive_damage("kee", damage, me);	//内伤，忽视护甲
		target->receive_wound("kee", damage, me);
		COMBAT_D->report_status(target);

		BUFF->add(target, debuff);		//减少parry debuff

		msv("$n奋力招架，然而力有不及连退数步，吐出一口鲜血。\n"NOR, me, target);
	}
	else {
		msv("$n奋力招架，不断将攻势瓦解。\n"NOR, me, target);
	}
	me->start_busy(1);
	return 1;
}

