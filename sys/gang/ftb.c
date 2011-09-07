
#include <ansi.h>

inherit __DIR__"_base";

void create()
{
	_props = ([
		"id"		: "ftb",
		"name"		: "斧头帮",
		"color"		: HIW,
		"location"	: "城西饮马峪",
		"slogan"	: "山贼，有前途的职业！",
		
		"npc"		: ([
			"guard"		: ([
				"ids"		: ({"fu shou", "axer", "guard"}),
				"name"		: "斧手",
				"family"	: "将军府",
				"weapon"	: "/d/obj/weapon/axe/bigaxe",				
				"props"		: ([]),
			]),
			"keeper"	: ([
				"ids"		: ({"er dangjia", "keeper"}),
				"name"		: "二当家",
				"title"		: "副帮主",
				"props"		: ([
					"age"		: 47,
					"long"		: "那蓬乱的头发，那淫荡的眼神，让人有种说不出的销魂，啊不，恶心。\n",
					"per"		: 5,
				]),
			]),
			"npc1"		: ([
				"ids"		: ({"xia zi", "blind man", "guard"}),
				"name"		: "瞎子",
				"props"		: ([
					"age"		: 37,
					"long"		: "闭上眼睛，温柔悦耳的声音；睁开眼睛，猥琐丑陋的男人。\n",
					"per"		: 7,
				]),
			]),
			"npc2"		: ([
				"ids"		: ({"wang cai", "dog", "guard"}),
				"name"		: "旺财",
				"title"		: "护院",
				"props"		: ([
					"race"		: "野兽",
					"age"		: 3,
					"long"		: "一只可爱的小狗。\n",
					"limbs"		: ({ "头部", "身体", "爪腿", "后腿", "尾巴" }),
					"verbs"		: ({ "bite", "claw" }),
					"chat_chance"	: 2,
					"chat_msg"	: ({
						"旺财用鼻子闻了闻你的脚。\n",
						"旺财执着的啃着一根绳子，仿佛那是一根骨头。\n",
					}),
					"block_msg"	: "$N狂吠着挡住$n的去路。\n",
				]),				
			]),
		]),

		"street"	: ([
			"short"		: "崖顶",
			"long"		: "\n山顶树木繁茂苍翠，崖下是寂静幽深的山谷，北面一条小路，蜿蜒\n通向一处山寨。\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/westway/yinma",
			"verb"	: "down",
			"msg1"	: "$N不顾一切地纵身跳下悬崖。",
			"msg2"	: "随着一声惨叫，$N从山顶上滚了下来，如同一滩鼻涕甩在地面。",
		]),

		"arrive"		: ([
			"dst"	: "/d/westway/yinma",
			"verb"	: "climb",
			"msg1"	: "$N攀着藤条，向山崖上爬去。",
			"msg2"	: "$N从崖下爬了上来，灰头土脸，满山草屑。",
		]),
	]);

	setup();
}

