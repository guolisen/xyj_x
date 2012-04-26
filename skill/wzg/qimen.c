// firefox 11/21/2009

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"qimen"
#define NAME			HIW"奇门遁甲阵"NOR
#define BUFF_DESC		"施放奇门遁甲。"
#define CD				20

string room_long = "\n"
	"你突然觉得天旋地转，日月星辰全部消失，再也分不清东西南北。\n"
	"眼前忽而漆黑一片，忽而亮光四射，忽而金星闪烁，耳边一时万籁\n"
	"俱寂，一时锣鼓喧天，一股惧意由泥丸升起，直冲天灵，身不由己\n"
	"地浑身直打颤。\n\n";


int checking(mapping buff);
int post_act(mapping buff);
mapping new_exits(object env);

int cast(object me, object target)
{
	object env = environment(me);
	mapping buff_ori = BUFF->find(me, ID);

	if(buff_ori) {
		BUFF->remove1(buff_ori);
	} else {
		int skill = me->query_skill("taiyi", 1);
		mapping env_req = ([
			"ex_value"	: ([ "no_change"	: "这里不能施放"NAME"。" ]),
			"ex_class"	: ([ "装修"			: "这里已经被人搞乱了。"]),
		]);
  		mapping req = ([
			"skill1"	: ([ "taiyi"		: 60]),
			"prop"		: ([ "mana"			: 400,	"sen"	: 100 ]),
		]);
		object barrier;

		if(!BTL->require(env, NAME, env_req)) return 1;
		if(!BTL->require(me, NAME, req)) return 1;
		if(!cd_start(me, ID, CD)) return notify_fail("你暂时还不能使用"NAME"。\n");

		seteuid(getuid());
		barrier = new(X_DIR"obj/fabao/barrier");
		barrier->set("host", me);

		msv(HIW"$N叽哩咕噜地念了几句咒语，突然间天空白光一闪!\n"NOR, me);
		if(barrier->move_to(env)) {
			mapping env_buff = ([
				"id"		: ID,
				"name"		: NAME,
				"class"		: "装修",
				"comment"	: BUFF_DESC,
				"replace"	: ([
					"short"		: NAME,
					"long"		: room_long,
					"exits"		: new_exits(env),
				]),
				"interval"	: 2,
				"timer_act"	: (: checking :),
				"post_act"	: (: post_act :),
				"_host"		: me,
				"_barrier"	: barrier,
			]);
			mapping buff = ([
				"id"		: ID,
				"name"		: NAME,
				"comment"	: BUFF_DESC,
				"_env"		: env,
			]);
			BTL->pay(me, req["prop"]);
			BUFF->link_each(env_buff, buff);
			BUFF->add(env, env_buff);
			BUFF->add(me, buff);
			me->start_busy(2);
		}
	}
	return 3;
}

int post_act(mapping buff)
{
	destruct(buff["_barrier"]);
	tell_room(buff["me"], "金光一闪，"NAME"消失了。\n"); 
	return 1;
}

//检查host位置，法术
int checking(mapping buff)
{
	object env = buff["me"];
	object host = buff["_host"];
	if(!host || environment(host) != env) return 0;
	if(host->query_skill_mapped("spells") != "taiyi") return 0;
	return 1;
}

//计算新出口，老出口不变，新加的出口指向本身
mapping new_exits(object env)
{
	mapping ori = env->query("exits");
	mapping rep = ([
		"east"		: env,		"west"		: env,
		"north"		: env,		"south"		: env,
		"northeast"	: env,		"southeast"	: env,
		"southwest"	: env,		"northwest"	: env,
	]);
	if(mapp(ori)) rep += ori;
	return rep;
}
