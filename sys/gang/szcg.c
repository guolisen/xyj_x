
#include <ansi.h>

inherit __DIR__"_base";

void create()
{
	mapping npc = ([
		"ids"		: ({"linshi gong", "guard"}),
		"name"		: "临时工",
		"title"		: "小贩杀手",
		"props"		: ([
			"age"			: 30,
			"chat_chance"	: 2,
			"chat_msg"		: ({
				"一声霹雳一把剑，一群猛犬是城管，钢铁的心肠黑色胆，综合治理保治安。\n",
				"杀声吓破乞丐胆，风林火山威名传，抢必狠，打必烂，砸敌摊位再罚款！\n",
			}),
			"block_msg"	: "$N挡住$n道：往哪儿走？先交罚款!\n",
		]),	
	]);

	_props = ([
		"id"		: "szcg",
		"name"		: "苏州城管",
		"color"		: HIR,
		"from"		: "苏州站",
		"location"	: "背阴山",
		"slogan"	: "抢必狠，打必烂，砸完再罚款！",
		
		"npc"		: ([
			"guard"		: ([
				"ids"		: ({"da shou", "guard"}),
				"name"		: "打手",
				"title"		: "执法员",
				"family"	: "阎罗地府",
				"weapon"	: "/d/qujing/qinglong/obj/stick",		
				"props"		: ([]),
			]),
			"keeper"	: ([
				"ids"		: ({"chumen jianxie", "keeper"}),
				"name"		: "出门见血",
				"title"		: "副队长",
				"props"		: ([
					"age"		: 47,
					"per"		: 5,
				]),
			]),
			"npc1"		: npc,
			"npc2"		: npc,
		]),

		"street"	: ([
			"short"		: "崖顶",
			"long"		: "\n山顶树木繁茂苍翠，崖下是寂静幽深的山谷，北面一条小路，蜿蜒\n通向一处山寨。\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/death/huangwai",
			"verb"	: "down",
			"msg1"	: "$N不顾一切地纵身跳下悬崖。",
			"msg2"	: "随着一声惨叫，$N从山顶上滚了下来，如同一滩鼻涕甩在地面。",
		]),

		"arrive"		: ([
			"dst"	: "/d/death/huangwai",
			"verb"	: "climb",
			"msg1"	: "$N挤进岩壁的缝隙，攀着藤条向山崖上爬去。",
			"msg2"	: "$N从崖下爬了上来，灰头土脸，满山草屑。",
		]),
	]);

	setup();
}

