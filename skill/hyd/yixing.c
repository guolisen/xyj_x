// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>

#define ID			"yixing"
#define NAME		HIY"移形换影"NOR
#define DURATION	120
#define CD			(7*60)

int on_timer(mapping buff);
mapping get_buff(object me, object target);

int cast(object me, object target)
{
	string msg;
	mapping buff_ori = BUFF->find(me, ID);

	if(!target && buff_ori) {
		BUFF->remove1(buff_ori);
		return 1;
	}
	if(!objectp(target) || !BTL->get_victim(me, target)) return notify_ok("你和谁移形换影？\n");
	else if(BUFF->find(target, ID)) return notify_ok("对方已经被调包了！\n");
	else if(BUFF->find2(target, "变身术")) return notify_ok("对方在变身中！\n");
	else {
		mapping req = ([
			"ex_temp"	: ([ "d_mana" : 1 ]),
			"ex_class"	: ([ "变身术" : 1 ]),
			"skill1"	: ([ "pingtian-dafa" : 120]),
			"prop"		: ([ "mana" : 300 ]),
		]);
		mapping cmp_parm = ([
			"prop"		: ([ "mana" : 1, "daoxing" : 1 ]),
			"skill"		: ([ "spells" : 3]),
			"temp"		: ([ "no_cast" : -1]),
		]);
		if(!BTL->require(me, NAME, req)) return 1;
		if(!cd_start(me, ID, CD)) return notify_fail("你暂时还不能使用"NAME"。\n");

		BTL->pay(me, req["prop"]);
		message_vision("$N大喝："NAME"！$N和$n如旋风一样转起来，分不清彼此。\n"
			"片刻之后两人停下来，显得都很狼狈。\n", me, target);

		if(BTL->cmp_random20(me, target, cmp_parm) >= 90) {
			mapping b1 = get_buff(me, target);
			mapping b2 = get_buff(target, me);
			BUFF->link_each(b1, b2);
			BUFF->add(me, b1);
			BUFF->add(target, b2);
		}		
		if(!target->is_busy()) target->start_busy(2);
		me->start_busy(2);
	}
	return 1;
}

mapping get_buff(object me, object target)
{
	mapping buff = ([
		"id"		: ID,
		"name"		: NAME,
		"comment"	: "和别人交换肉身。",
		"class"		: "变身术",
		"duration"	: DURATION,
		"temp"		: ([	//换外观
			"apply/id"		: target->parse_command_id_list(),
			"apply/name"	: ({ target->name() }),			
			"apply/short"	: ({ target->short() }),
			"apply/long"	: ({ target->long() }),
			"no_heal_up/"ID : 1,
		]),
		"add_apply"	: ([	//换护甲容貌
			//"armor"			: target->query_temp("apply/armor") - me->query_temp("apply/armor"),
			"personality"	: target->query_per() - me->query_per(),
		]),
		"add"		: ([	//换血
			"max_kee"		: target->query("max_kee") - me->query("max_kee"),
			"eff_kee"		: target->query("eff_kee") - me->query("eff_kee"),
			"kee"			: target->query("kee") - me->query("kee"),
		]),
		"stop_msg"	: HIY"恍惚间$N仿佛突然醒了过来，对周围很陌生。",
		"interval"	: 1,
		//"timer_act"	: (: on_timer :),
		"post_act"	: function(mapping buff) {
			object me = buff["me"];
			me->receive_curing("kee", 1);
			me->receive_heal("kee", 1);
		},
		"data"		: (["target" : target ]),
	]);
	tell_object(me, "你感觉身上有些异样。\n");
	return buff;
}

int on_timer(mapping buff)
{
	object me = buff["me"];
	object target = buff["data"]["target"];
	mapping b2 = BUFF->find(target, ID);

	//TODO:做点什么？
	return 1;
}
