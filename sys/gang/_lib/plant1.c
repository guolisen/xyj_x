/*

目前xyj的果蔬大概有这些
猕猴桃;碧藕;交梨;火枣;人参果
黄瓜;青菜;葫芦;西瓜;茄子;白菜
一种是设置种植相关技能，用技能和植物本身结果几率限制结出果实的成功率
一种是没有种植技能，对种子的类别做限制，比如rsg种子出现的概率很低，
植物本身结果几率决定结出果实的成功率
可以采用暗箱种子的方法，玩家不能看出来是哪种类型的种子，
必须等到发芽后才知道。
不同植物，出了结果率不同，生长周期也不同，越好的植物，周期越长
对于同一种植物，累计失败次数达到一定值必然成功
对于看到不是自己想要的种子就荒弃不中的植物，不予计数
果实的成功率和玩家等级如何挂钩，一定需要一个判断去限制白板种植成功率，不然大米泛
果实成堆，可以借用top值或者其他标准



植物	
	阶段	种子	嫩芽	小苗	小树	果树
	


花园，
	松土loose	
	
兽栏
	清理	

植物		温度	幼苗期	生长期	成熟期	次数	枯萎期	功效

蓝色小草	0-5		
雪莲		0-5
碧藕
火枣
蟠桃
人参果
猕猴桃

熔炉，炼制消耗品，提升法宝
丹药

道行丹
武学丹
济神丹
倒马毒	提升真身毒性

定风丹

武器	
法宝

兽栏


"墨麒麟"	({"mo qilin", "qilin"})				/d/sea/npc/beast/beast4	麒麟角
"一头浑身墨绿的麒麟，端是一头神兽。\n"

"恶龙"		({"dragon"})						/d/qujing/wudidong/npc/dragon
"一条张牙舞爪的恶龙，样子十分可怕。\n"
"火龙"		({"huo bing", "bing"})				/d/dntg/laojunlu/npc/huobing
"火马",
"火鸦",
"火鼠",
"天宫火部战将，久精沙场。\n"

"桃核"		({ "tao he", "taohe","he" })		/d/dntg/pantao/obj/taohe

HIB"蓝色小草"NOR	({"xiao cao", "xiaocao", "cao"}))	/d/obj/misc/xiaocao
"这种草叶尖圆润，色泽幽蓝，的确好看。 \n"

"雪莲"		({"xue lian", "xuelian", "lian"}))			/d/moon/obj/xuelian
"一朵雪莲花，只生长于绝峰极寒之处。\n"

YEL"猕猴桃"NOR	({"mihou tao","mihoutao","tao"})	/d/obj/drug/mihoutao
"黄橙橙的一颗猕猴桃，真叫人垂涎欲滴。\n"

RED"火枣"NOR	({"huo zao","zao"})
"unit", "枚"
"一枚采自海中仙山，色红如火的香枣。\n"			/d/obj/drug/huozao


"朱睛冰蟾"										/d/xueshan/npc/hama		蟾酥
"五彩蜘蛛"	({ "wucai zhizhu", "zhizhu" })		/d/xueshan/npc/zhizhu	蜘蛛丝
"双尾蝎"	({ "xiezi jing", "xiezi", "jing" })	/d/xueshan/npc/xiezi	倒马毒
"赤练小蛇"	({ "chilian xiaoshe", "she" })		/d/xueshan/npc/she		蛇毒
"百足蜈蚣", ({ "baizu wugong", "wugong" })		/d/xueshan/npc/wugong	毒液



生命周期

气候/温度范围	最低是大雪山，最高是火焰山


        message_vision("$N使出全身的力气去推那石桌，石桌竟被推开了，钻出两条火龙来n",who);
        message_vision("\n火龙口一张，对准$N喷出了两股粉金融玉的火柱。\n", who);
        if( (int)who->query_temp("push_time") > 3) {
                call_out("faint_him", 0, who);
        return 1;
	}

        message_vision("\n$N被烧的遍体粼伤，惨不忍睹。\n", who);





*/

//pick cai采摘

mapping info = ([
	"plant"		: ([
		"birthday"		: 100,		//栽种时间
		""
	]),
	"animal"	: ([

	]),
	"stove"		: ([
	]),
]);

mapping peach = ([
	"name"			: "桃树",
	"ids"			: ({"tao shu", "peach", "tree"}),
	"long"			: "\n一棵桃树。随着清风吹来树叶沙沙作响。\n",

	"req"			([ "outdoors" : 1, "temperature" : 20 ]);

	"life-span"		: 10,
	"life_old"		: "干枯的",
	"life_end"		: "$N把$n连根拔起，随手扔到了墙外。",

	"fruit"			: "/d/xiantao",
	"fruit_amount"	: 0,

	//"init_msg"		: ({"随着清风吹来%s叶沙沙作响。"}),
	
	"work_verb"		: ({"shifei", "manure"}),
	"work_msg"		: "$N开始卖力的施肥，一会就累得筋疲力尽。\n",

	"gather_verb"	: ({"cai", "pick"}),
	"gather_msg0"	: "$N在$n上搜索了半天，什么也没发现。\n",
	"gather_msg1"	: "$N从$n上摘下$n2。\n",
	
	"feed_verb"		: ({"reng", "bury"}),
	"feed_msg0"		: "$N想将$n埋了给$n2做肥料，想想又觉得不忍。",
	"feed_msg1"		: "$N把$n扔在$n2下，三下两下当肥料埋了。",
	
	"seed"			: "/d/taohe",
	"spread_verb"	: ({"zhong", "spread"}),
	"spread_msg0"	: "这里不能种植更多的作物了。",
	"spread_msg1"	: "$N满怀期盼的把一颗$n埋在土里，轻轻撒上水。",
]);

mapping hama = ([
	"name"			: "朱睛冰蟾",
	"ids"			: ({"bing chan", "hama", "toad"}),
	"long"			: "\n一只大蟾蜍，通体雪白，眼珠却血也般红，模样甚是可爱，却也不\n见有何珍异之处。\n",

	"req"			([ "outdoors" : 0,  "temperature" : 20 ]);

	"life-span"		: 10,
	"life_old"		: "老迈的",
	"life_end"		: "$N打开兽栏把$n放了出来，$n在$N腿上蹭了蹭，慢慢爬开了。",

	"fruit"			: "/d/chansu",
	"fruit_amount"	: 0,
	
	"work_verb"		: ({"qingli", "clean"}),
	"work_msg"		: "$N开始卖力的清理兽栏，一会就累得筋疲力尽。\n",
		
	"gather_verb"	: ({"pai", "pat"}),
	"gather_msg0"	: "$N轻轻拍了拍$n，但它好像没任何反应。\n",
	"gather_msg1"	: "$N轻轻拍了拍$n，从耳朵后挤出$n2。\n",
	
	"feed_verb"		: ({"reng", "feed"}),
	"feed_msg0"		: "$N想将$n喂$n2，想想又觉得不忍。",
	"feed_msg1"		: "$N将$n扔进兽栏，$n2上前一口吞下。",

	"seed"			: "/d/hama",
	"spread_verb"	: ({"yang", "breed"}),
	"spread_msg0"	: "这里不能圈养更多的动物了。",
	"spread_msg1"	: "$N你把$n放进兽栏，满心欢喜的关上门。",
]);


mapping daoxingdan = ([
	"name"			: "丹炉",
	"ids"			: ({ "dan lu", "lu", "stove" }),
	"long"			: "\n这是一鼎一人多高的紫色丹炉。上面铭刻着风火雷电，五行八卦各\n种图案。\n",

	"req"			([ "outdoors" : 0 ]);

	"fruit"			: "/d/daoxingdan",
	"fruit_amount"	: 0,
	
	"work_verb"		: ({"huo", "fire"}),
	"work_msg"		: "$N吐出一团火，缓缓注入炉中，接着瘫倒在地。\n",

	"gather_verb"	: ({"mo", "grope"}),
	"gather_msg0"	: "$N把手伸进$n里，一团烈焰喷出，差点把$N烧焦。\n",
	"gather_msg1"	: "$N把手伸进$n里，转眼摸出%s。\n",

	"feed_verb"		: ({"reng", "smelt"}),
	"feed_msg0"		: "$N想将$n扔进%s，想想又觉得不忍。",
	"feed_msg1"		: "$N将$n扔进丹炉，转眼$n就被烈焰吞噬了。",

	"seed"			: "/d/danlu",
	"spread_verb"	: ({"fang", "place"}),
	"spread_msg0"	: "这里不能放置更多的%s了。",
	"spread_msg1"	: "$N你把$n放下，安置妥当。",

]);

//树
//丹炉要靠扔进去的东西决定出产类型


mapping chansu = ([
	"name"			:"蟾酥",
]);
