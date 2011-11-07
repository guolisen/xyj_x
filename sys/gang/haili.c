
#include <ansi.h>

inherit __DIR__"_base";

void create()
{
	_props = ([
		"id"		: "haili",
		"name"		: "海蛎",
		"color"		: HIC,
		"from"		: "青岛站",
		"location"	: "东海之滨",
		"slogan"	: "哈啤酒，上蛤蜊！",
		
		"npc"		: ([
			"guard"		: ([
				"ids"		: ({"xian ge", "boy", "guard"}),
				"name"		: "小哥",
				"family"	: "将军府",
				"weapon"	: "/d/obj/weapon/axe/bigaxe",				
				"props"		: ([ 
					"gender"	: "男性",
					"long"		: "青岛小哥不好惹，惹了卯你眼！\n",
				]),
			]),
			"keeper"	: ([
				"ids"		: ({"lao bazi", "keeper"}),
				"name"		: "老巴子",
				"title"		: "管家",
				"props"		: ([
					"age"		: 60,
					"gender"	: "男性",
					"long"		: "一位混迹青岛多年的老巴子，丝毫看不出一点儿农村气息。\n",
				]),
			]),
			"npc1"		: ([
				"ids"		: ({"da man", "girl", "guard"}),
				"name"		: "大嫚",
				"props"		: ([
					"age"		: 26,
					"per"		: 30,
					"gender"	: "女性",
					"long"		: "一位从背后看10分的美女，没钱没车没房离她远点。\n",
				]),
			]),
			"npc2"		: ([
				"ids"		: ({"xiao man", "girl", "guard"}),
				"name"		: "小嫚",
				"props"		: ([
					"age"		: 16,
					"per"		: 30,
					"gender"	: "女性",
					"long"		: "热裤、抹胸，一开口一股浓重的海蛎子味儿，一位标准的90后青岛小嫚。\n"
				]),				
			]),
		]),

		"street"	: ([
			"short"		: "崖顶",
			"long"		: "\n山顶树木繁茂苍翠，崖下是一望无垠的大海，北面一条小路，蜿蜒\n通向一处山寨。\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/changan/eastseashore",
			"verb"	: "down",
			"msg1"	: "$N不顾一切地纵身跳下悬崖。",
			"msg2"	: "随着一声惨叫，$N从山顶上滚了下来，如同一滩鼻涕甩在海滩上。",
		]),

		"arrive"		: ([
			"dst"	: "/d/changan/eastseashore",
			"verb"	: "climb",
			"msg1"	: "$N攀着藤条，向山崖上爬去。",
			"msg2"	: "$N从崖下爬了上来，灰头土脸，满山草屑。",
		]),
	]);

	setup();
}

