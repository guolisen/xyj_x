// by firefox & shines 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>

#define BUFF_ID			"zhenshen2"
#define BUFF_NAME		"真身"

#define DURATION		120		//技能持续时间
#define CD				5		//技能冷却时间


mapping query_trait(object who);
int on_timer(mapping buff);

int exert(object me, object target)
{
	mapping buff_ori = BUFF->find(me, BUFF_ID);

	if(buff_ori) {									//解除变身
		BUFF->remove(buff_ori);
	} else {										//变身
		int skill = me->query_skill("dragonforce", 1);
		int kee_gain = skill * 4;
		mapping req = ([
			"cd"		: ([ BUFF_ID	: 1 ]),
			"ex_temp"	: ([ "no_wield" : 1, "powerup" : 1, "d_mana" : 1]),
			"ex_class"	: ([ "变身术" : 1 ]),
			"skill1"	: ([ "dragonforce"	: 250]),
			"prop"		: ([ "force"		: 300,	"kee"		: 150,	"sen"		: 150]),
		]);
		mapping trait = query_trait(me);
		
		mapping buff = ([
			"id"		: BUFF_ID,
			"name"		: BUFF_NAME,
			"comment"	: "变身成一条龙，拥有龙的顽强生命和强大力量。",
			"class"		: "变身术",
			"duration"	: DURATION,
			"temp"		: ([
				"apply/name"	: ({ trait["name"] }),
				"apply/id"		: ({ trait["id"] }),
				"apply/short"	: ({ trait["short"] }),
				"apply/long"	: ({ trait["long"] + NOR"\n" }),
				"no_wield"		: 1,
				"powerup"		: 1,
			]),
			"add_apply"	: ([
				"armor"		: skill / 2,		//TODO:状态增强调节
				"unarmed"	: skill / 2,
				"parry"		: skill,			//胳膊粗，能招架，combatd中空手有惩罚
				"force"		: skill * 2,		//挽救roar
				"dodge"		: -skill / 2,		//体型太大，难闪转腾挪
				"personality"	: -30,			//龙比较狰狞
			]),
			"replace"	: ([
				"limbs"		: ({ "头部", "身体", "前爪", "尾巴", "肚皮", "后爪"}),
				"force_factor" : (int)me->query_skill("force") / 2 + skill,
			]),
			"add"		: ([
				"max_kee"		: kee_gain,
				"kee"			: kee_gain,
			]),
			"start_msg"	: HIC"$N凝神运气，大喝一声，血肉之躯竟化为一条张牙舞爪的"
				+ trait["name"] + HIC"，端地杀气逼人。",
			"stop_msg"	: HIC"$N的龙神心法运行一周天完毕，身体也渐渐复原了。",
			"post_act"	: function(mapping buff) {
				object me = buff["me"];
				me->receive_curing("kee", 1);
				me->receive_heal("kee", 1);
			},
			"interval"	: 4,
			"timer_act"	: (: on_timer :),	
		]);

		if(!BTL->require(me, BUFF_NAME, req)) return 1;
		BTL->pay(me, (["force" : skill]));
		BUFF->add(me, buff);
		BUFF->start_cd2(me, buff, CD);

		me->receive_curing("kee", kee_gain);
		me->start_busy(1);
	}
	return 1;
}

//定时触发龙的特效
int on_timer(mapping buff)
{
		/*object enemy = query_temp("last_damage_from");
	object weapon;
	if(enemy && weapon = enemy->query_temp("weapon")) {
		damage = weapon->query("weapon_prop/damage");
	}
	//兵器融化，$N的武器仿佛要被$n身上的火焰融化/烧着了set("material", "steel");
	//query("material") != "ice" ) "bone");*/

	return 1;
}

//获取龙的种类与特征
mapping query_trait(object who)
{
	mapping trait = ([
		"seashentong"	: ([
			"name"			: "苍龙",
			"long"			: "一条苍龙，身似长蛇、麒麟首、鲤鱼尾、面有长须、犄角似鹿、有五爪。",
			"color"			: HIC,
			"act_prob"		: 50,
			"act"			: function(object target, mapping buff) {
				//伤害？
			},
		]),
		"taiyi"	: ([
			"name"			: "火龙",
			"long"			: "一条火龙，全身有火缠绕。",
			"color"			: HIR,
			"act_prob"		: 50,
			"act"			: function(object target, mapping buff) {
			},
		]),
		"gouhunshu"		: ([
			"name"			: "蟠龙",
			"long"			: "一条蟠龙身长四丈，青黑色，赤带如锦文。",
			"color"			: HIB,
			"act_prob"		: 50,
			"act"			: function(object target, mapping buff) {
				//中毒
			},
		]),
		"dengxian-dafa"	: ([
			"name"			: "冰龙",
			"long"			: "一条冰龙，寒气逼人。",
			"color"			: HIW,
			"act_prob"		: 50,
			"act"			: function(object target, mapping buff) {
				//no_move
			},
		]),
		"misc"	: ([
			"name"			: "蛟龙",
			"long"			: "一条蛟龙，状如蛇，首如虎，声如牛，长数丈。",
			"color"			: HIG,
			"act_prob"		: 50,
			"act"			: function(object target, mapping buff) {
				//
			},
		]),
	]);
	mapping m;
	string spells = who->query_skill_mapped("spells");
	if(!spells || !trait[spells]) spells = "misc";
	if(spells == "pingtian-dafa") spells = "taiyi";

	m = trait[spells];
	if(!m["id"]) m["id"] = "dragon";
	if(!m["short"])
		m["short"] = m["color"] + m["name"] + NOR + "(Dragon)";
	return m;
}
