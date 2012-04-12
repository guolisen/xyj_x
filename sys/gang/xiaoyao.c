
#include <ansi.h>

inherit __DIR__"_base";

void create()
{
	_props = ([
		"id"		: "xiaoyao",
		"name"		: "逍遥仙",
		"color"		: HIM,
		"from"		: "-",
		"location"	: "百花谷",
		"slogan"	: "百花丛中 逍遥自在！",
		
		"npc"		: ([
			"guard"		: ([
				"ids"		: ({"xian tong", "tong", "guard"}),
				"name"		: "仙童",
				"family"	: "将军府",
				"weapon"	: "/d/obj/weapon/axe/bigaxe",				
				"props"		: ([ "gender" : "男性" ]),
			]),
			"keeper"	: ([
				"ids"		: ({"tiao tiao", "keeper"}),
				"name"		: "跳跳",
				"title"		: "纯新人",
				"props"		: ([
					"age"		: 10,
					"per"		: 5,
				]),
			]),
			"npc1"		: ([
				"ids"		: ({"xian zi", "girl", "guard"}),
				"name"		: "仙子",
				"props"		: ([
					"age"		: 20,
					"per"		: 30,
					"gender"	: "女性",
				]),
			]),
			"npc2"		: ([
				"ids"		: ({"xian he", "he", "guard"}),
				"name"		: "仙鹤",
				"props"		: ([
					"race"		: "野兽",
					"age"		: 3,
					"limbs"		: ({ "头部", "身体", "爪腿", "后腿", "尾巴" }),
					"verbs"		: ({ "bite", "claw" }),

					"block_msg"	: "$N展翅挡住$n的去路。\n",
				]),				
			]),
		]),

		"street"	: ([
			"short"		: "崖顶",
			"long"		: "\n山顶树木繁茂苍翠，崖下是寂静幽深的山谷，北面一条小路，蜿蜒\n通向一处山寨。\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/penglai/baihuagu1",
			"verb"	: "down",
			"msg1"	: "$N不顾一切地纵身跳下悬崖。",
			"msg2"	: "随着一声惨叫，$N从山顶上滚了下来，如同一滩鼻涕甩在地面。",
		]),

		"arrive"		: ([
			"dst"	: "/d/penglai/baihuagu1",
			"verb"	: "climb",
			"msg1"	: "$N挤进岩壁的缝隙，攀着藤条向山崖上爬去。",
			"msg2"	: "$N从崖下爬了上来，灰头土脸，满山草屑。",
		]),
	]);

	setup();
}

