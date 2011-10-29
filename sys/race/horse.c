// by firefox 11/21/2009

//特技，冲锋，一枪将某某挑于马下


#include <ansi.h>

void create()
{
	set_name("马", ({"horse"}));
	set("race", "野兽");
	set("age", 10);
	set("combat_exp", 10000);
	set("limbs", ({ "头部", "身体", "前脚", "后脚", "尾巴" }) );
	set("verbs", ({ "bite"}));

	set("ride/msg", "骑");
	set("ride/dodge", 20);
}

#define DESC			"一匹神骏的千里马。"
#define DESC8			"一匹骏马，穆王八骏之一。"
#define DESC9			"一匹骏马，文帝九逸之一。"
#define DESC_LEE		"传闻是李元霸的坐骑，主人已逝，良驹何往？"

void init_var()
{
	_subs = ([

		"黄骠透骨龙"	: ([
			"ids"			: ({"yellow dragon", "dragon", "horse"}),
			"long"			: "一匹骁勇矫健的战马，通体橙黄，毛无杂色。",
			"color"			: HIY,
		]),
		"千里一盏灯"	: ([
			"ids"			: ({"red lamp", "lamp", "horse"}),
			"long"			: DESC_LEE,
			"color"			: HIR,
		]),
		"万里烟云罩"	: ([
			"ids"			: ({"red lamp", "lamp", "horse"}),
			"long"			: DESC_LEE,
		]),
		"赛龙五斑驹"	: ([
			"ids"			: ({"spot horse", "horse"}),
			"long"			: "一匹满身斑点的骏马。",
			"color"			: HIC,
		]),
		"没角癞麒麟"	: ([
			"ids"			: ({"scabies kirin", "kirin", "horse"}),
			"long"			: "一匹满身疙瘩的骏马",
			"color"			: HIB,
		]),
		"踏乌白雪马"			: ([
			"ids"			: ({"snow horse", "horse"}),
			"long"			: "一匹通体雪白的骏马。",
			"color"			: HIW,
		]),
		"赤炭火龙驹"			: ([
			"ids"			: ({"fire horse", "horse"}),
			"long"			: "一匹通体火红的骏马。",
			"color"			: HIR,
		]),
		"金睛兽"			: ([
			"ids"			: ({"jinjing shou", "shou", "horse"}),
			"long"			: "一匹眼露金光的骏马。" ,
			"color"			: HIY,
		]),


		"骅骝"			: ([
			"ids"			: ({"hua liu", "horse"}),
			"long"			: "色如华而赤，穆王八骏之一。",
			"color"			: RED,
		]),
		"骐骥"			: ([
			"ids"			: ({"qi ji", "horse"}),
			"long"			: DESC,
		]),
		"绿耳"			: ([
			"ids"			: ({"lu er", "horse"}),
			"long"			: DESC8,
		]),
		"纤离"			: ([
			"ids"			: ({"xian li", "horse"}),
			"long"			: DESC,
		]),

		"龙媒骏"			: ([
			"ids"			: ({"longmei jun", "jun", "horse"}),
			"long"			: DESC,
		]),
		"紫燕骝"			: ([
			"ids"			: ({"ziyan liu", "liu", "horse"}),
			"long"			: DESC9,
			"color"			: MAG,
		]),
		"挟翼"			: ([
			"ids"			: ({"xie yi", "horse"}),
			"long"			: "背生双翼，形似鹏鸟，能翱翔九州，穆王八骏之末。",
		]),
		"骕骦"			: ([
			"ids"			: ({"su shuang", "horse"}),
			"long"			: DESC,
			"color"			: WHT,
		]),

		
		"駃騠，"			: ([
			"ids"			: ({"jue ti", "horse"}),
			"long"			: "骡骡之子，千里駃騠，与汗血宝马齐名。",
		]),
		"银騔"			: ([
			"ids"			: ({"yin ge", "horse"}),
			"long"			: DESC,
			"color"			: WHT,
		]),
		"騕褭"			: ([
			"ids"			: ({"yao niao", "horse"}),
			"long"			: DESC,
		]),
		"飞黄"			: ([
			"ids"			: ({"fei huang", "horse"}),
			"long"			: DESC,
		]),

		
		"騊駼"			: ([
			"ids"			: ({"tao tu", "horse"}),
			"long"			: "古神兽。产於北海，形状如马，色青。。",
			"color"			: HIC,
		]),
		"翻羽"			: ([
			"ids"			: ({"fan yu", "horse"}),
			"long"			: "奔跑如飞翔，穆王八骏之一。",
		]),
		"赤兔"			: ([
			"ids"			: ({"chi tu", "horse"}),
			"long"			: "良马一匹，日行千里，渡水登山，如履平地。",
			"color"			: RED,
		]),
		"超光"			: ([
			"ids"			: ({"chao guang", "horse"}),
			"long"			: DESC8,
		]),

		
		"逾辉"			: ([
			"ids"			: ({"yu hui", "horse"}),
			"long"			: DESC8,
		]),
		"弥景"			: ([
			"ids"			: ({"mi jing", "horse"}),
			"long"			: DESC,
		]),
		"腾雾"			: ([
			"ids"			: ({"teng wu", "horse"}),
			"long"			: DESC8,
		]),
		"胜黄"			: ([
			"ids"			: ({"sheng huang", "horse"}),
			"long"			: "传说中的神驹。其状如狐，背上有两角。",
			"color"			: YEL,
		]),

		"追风"			: ([
			"ids"			: ({"zhui feng", "horse"}),
			"long"			: DESC,
		]),
		"绝地"			: ([
			"ids"			: ({"jue di", "horse"}),
			"long"			: DESC,
		]),
		"飞翻"			: ([
			"ids"			: ({"fan fei", "horse"}),
			"long"			: DESC,
		]),
		"奔霄"			: ([
			"ids"			: ({"ben xiao", "horse"}),
			"long"			: DESC8,
		]),

		"逸飘"			: ([
			"ids"			: ({"yi piao", "horse"}),
			"long"			: DESC,
		]),
		"赤电"			: ([
			"ids"			: ({"chi dian", "horse"}),
			"long"			: DESC9,
			"color"			: HIR,
		]),
		"铜爵"			: ([
			"ids"			: ({"tong jue", "horse"}),
			"long"			: DESC,
			"color"			: YEL,
		]),
		"浮云"			: ([
			"ids"			: ({"fu yun", "horse"}),
			"long"			: DESC9,
			"color"			: WHT,
		]),

		"骢珑"			: ([
			"ids"			: ({"cong long", "horse"}),
			"long"			: "一匹骏马，毛色青白相杂，世传青海骢者是也。",
		]),
		"虎剌"			: ([
			"ids"			: ({"hu ci", "horse"}),
			"long"			: DESC,
		]),
		"绝尘"			: ([
			"ids"			: ({"jue chen", "horse"}),
			"long"			: DESC9,
		]),
		"紫鳞"			: ([
			"ids"			: ({"zi lin", "horse"}),
			"long"			: DESC8,
			"color"			: MAG,
		]),

		"绝群"			: ([
			"ids"			: ({"jue qun", "horse"}),
			"long"			: DESC9,
		]),
		"逸群"			: ([
			"ids"			: ({"yi qun", "horse"}),
			"long"			: DESC9,
		]),
		"禄螭骢"			: ([
			"ids"			: ({"luli cong", "horse"}),
			"long"			: DESC9,
		]),
		"龙子"			: ([
			"ids"			: ({"ling zi", "horse"}),
			"long"			: DESC9,
		]),
		"嶙驹"			: ([
			"ids"			: ({"lin ju", "horse"}),
			"long"			: DESC9,
		]),

	]);
	
	//特征，坐骑只能加dodge
	_traits = ([
		//初始属性
		"prop"	: ([
			"dodge"	: 1,
		]),

		//按百分比加成的属性
		"prop_x"	: ([
			"dodge"			: 100,
		]),

		"come_msg"	: "一声长嘶，$n从滚滚烟尘中疾驰而来。",
		"leave_msg"	: "一声长嘶，$n绝尘而去。",
	]);
}


