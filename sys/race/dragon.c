// by firefox 11/21/2009


小白龙：龙舒利爪，猴举金箍。那个须垂白玉线，这个眼幌赤金灯。那个须下明珠喷彩雾，这个手中铁棒舞狂风。那个是迷爷娘的业子，这个是欺天将的妖精。他两个都因有难遭磨折，今要成功各显能。主

/d/sea/girl3

/d/sea/npc/longnu





/*
飞腾变化，绕雾盘云。
玉爪垂钩白，银鳞舞镜明。
髯飘素练根根爽，角耸轩昂挺挺清。
磕额崔巍，圆睛幌亮。
隐显莫能测，飞扬不可评。
祷雨随时布雨，求晴即便天晴。
这才是有灵有圣真龙象，祥瑞缤纷绕殿庭。
*/
mapping _trait = ([
	"苍龙"	: ([
		"ids"			: ({"cang dragon", "dragon"}),
		"long"			: "一条苍龙，身似长蛇、麒麟首、鲤鱼尾、面有长须、犄角似鹿、有五爪。",
		"color"			: HIC,
		"spells"		: "seashentong",
		"act"			: function(object target, mapping buff) {
			//伤害？
		},
	]),
	"火龙"	: ([
		"ids"			: ({"fire dragon", "dragon"}),
		"long"			: "一条火龙，全身有火缠绕。",
		"color"			: HIR,
		"spells"		: "taiyi",
		"act"			: function(object target, mapping buff) {
		},
	]),
	"毒龙"		: ([
		"ids"			: ({"poison dragon", "dragon"}),
		"long"			: "一条蟠龙身长四丈，青黑色，赤带如锦文。",
		"color"			: HIB,
		"spells"		: gouhunshu,
		"act"			: function(object target, mapping buff) {
			//中毒
		},
	]),
	"冷龙"	: ([
		"ids"			: ({"cold dragon", "dragon"}),
		"long"			: "一条冷龙，寒气逼人。",
		"color"			: HIW,
		"spells"		: "dengxian-dafa",
		"act"			: function(object target, mapping buff) {
			//no_move
		},
	]),
	"蛟龙"	: ([
		"ids"			: ({"cang long", "long", "dragon"}),
		"long"			: "一条蛟龙，状如蛇，首如虎，声如牛，长数丈。",
		"color"			: HIG,
		"spells"		: 50,
		"act"			: function(object target, mapping buff) {
			//
		},
	]),
]);

mapping buff = ([

	"add_apply"	: ([
		"armor"		: 100,
		"unarmed"	: 100,
		"parry"		: 100,			//胳膊粗，能招架，combatd中空手有惩罚
		"force"		: 100,			//挽救roar
		"dodge"		: 100,			//体型太大，难闪转腾挪
		"personality"	: -30,			//龙比较狰狞
	]),

	"replace"	: ([
		"limbs"		: ({ "头部", "身体", "前爪", "尾巴", "肚皮", "后爪"}),
	]),

	"add"		: ([
		"max_kee"	: 100,
		"kee"		: 100,
	]),
	"start_msg"	: HIC"$N化为一条张牙舞爪的%s"HIC"，端地杀气逼人。",
	"stop_msg"	: HIC"$N的龙神心法运行一周天完毕，身体也渐渐复原了。",
	"post_act"	: function(mapping buff) {
		object me = buff["me"];
		me->receive_curing("kee", 1);
		me->receive_heal("kee", 1);
	},
	"interval"	: 4,
	"timer_act"	: (: on_timer :),	
]);

