// by firefox 11/21/2009

#include <ansi.h>
#include <xyj_x.h>

inherit SSERVER;

#define CD			5		//技能冷却时间
#define DURATION	60		//技能持续时间

#define BUFF_ID		"sanmei2"
#define BUFF_NAME	HIR"三昧真火"NOR
#define BUFF_DESC	HIR"浓烟滚滚，烈焰翻腾，一片火海。"NOR

#define DEBUFF_ID	"burning"
#define DEBUFF_NAME	HIR"烈火焚身"NOR
#define DEBUFF_DESC	"身上着火，视觉模糊，命中下降。"

int burning(mapping buff);

int cast(object me)
{
	object env = environment(me);
	mapping buff_ori = BUFF->find(me, BUFF_ID);

	if(buff_ori) {
		BUFF->remove1(buff_ori);
	} else {
		int skill = me->query_skill("pingtian-dafa", 1);
		mapping env_req = ([
			"ex_value"	: ([ 
				"no_change"	: "这里不能施放"BUFF_NAME"。",
				"water"		: "无法在水中放火。",
			]),
			"ex_class"	: ([ "装修"		: "这里已经被人搞乱了。"]),
		]);
		mapping req = ([
			"cd"		: ([ BUFF_ID	: 1 ]),
			"skill1"	: ([ "pingtian-dafa" : 100 ]),
			"prop"		: ([ "mana"	: skill ]),
		]);
		mapping env_buff = ([
			"id"		: BUFF_ID,
			"name"		: BUFF_NAME,
			"class"		: "装修",
			"comment"	: BUFF_DESC,
			"duration"	: DURATION + 4,				//纵火者离线，房间也能回复
			"replace"	: ([ "long" : env->query("long") + "    "BUFF_DESC"\n" ]),
			"post_act"	: function(mapping buff) {
				tell_room(buff["me"], HIY "大火渐渐熄灭，四周一片焦土。\n" NOR);
			},
		]);
		mapping buff = ([
			"id"		: BUFF_ID,
			"name"		: BUFF_NAME,
			"comment"	: "正在施放三昧真火。",
			"duration"	: DURATION,			
			"interval"	: 6,
			"timer_act"	: (: burning :),
			"_env"		: env,
		]);
		if(!BTL->require(env, BUFF_NAME, env_req)) return 1;
		if(!BTL->require(me, BUFF_NAME, req)) return 1;

		BTL->pay(me, req["prop"]);
		message_vision(
			"\n$N往自家鼻子上捶了两拳，念个咒语，口中喷火，鼻子冒烟，顷刻间：\n\n"
			HIR"炎炎烈烈盈空燎，赫赫威威遍地红。却似火轮飞上下，犹如炭屑舞西东。\n\n"NOR,
			me
		);
		BUFF->link_each(env_buff, buff);
		BUFF->add(env, env_buff);
		BUFF->add(me, buff);
		BUFF->start_cd2(me, buff, CD);
		
		me->start_busy(1);
	}
	return 1;
}

void burn(object me, object target)
{
	int skill1 = me->query_skill("spells");
	int skill2 = target->query_skill("spells");
	string spells = target->query_skill_mapped("spells");
	int diff;
	
	if(spells != "pingtian-dafa") skill2 /= 3;		//TODO:火抗系数
	diff = skill1 - skill2;

	if(diff > 10) {
		mapping debuff = ([
			"id"		: DEBUFF_ID,
			"name"		: DEBUFF_NAME,
			"comment"	: DEBUFF_DESC,
			"class"		: "诅咒",
			"duration"	: 5,					//离开火海，状态也要一段时间恢复
			"add_apply"		: ([
				"attack"	: -diff,				//烧的视觉模糊，命中下降
				"armor"		: -diff / 2,			//衣服烧焦了，负护甲往往带来wound上升
				"personality"	: -20,			//毁容了
			]),
		]);
		int damage = diff;						//这里或许该和法力道行相关
		BUFF->add(target, debuff);

		target->receive_damage("kee", damage, me);
		target->receive_wound("kee", damage);
		
		tell_object(target, "你被烧得焦头烂额！\n");
		COMBAT_D->report_status(target);

		BTL->fight_enemy(target, me);
	}
}

int burning(mapping buff)
{
	object me = buff["me"];
	object env = environment(me);
	
	if(env != buff["_env"]) return 0;

	tell_room(env, "熊熊燃烧的" HIR "大火"  NOR "仿佛要吞噬一切。\n");

	foreach(object who in all_inventory(env)) {
		if(!living(who) || !who->is_fighting(me)) continue;
		burn(me, who);
	}
	return 1;
}
