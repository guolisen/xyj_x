
#include <ansi.h>

inherit __DIR__"_base";

void create()
{
	_props = ([
		"id"		: "dongxing",
		"name"		: "东星",
		"color"		: HIM,
		"from"		: "-",
		"location"	: "宝象山湾",
		"slogan"	: "聊天打诨，赌博梭哈！",
		
		"npc"		: ([
			"guard"		: ([
				"ids"		: ({"xiao hunhun", "hunhun", "guard"}),
				"name"		: "小混混",
				"family"	: "将军府",
				"weapon"	: "/d/gao/obj/blade",				
				"props"		: ([]),
			]),
			"keeper"	: ([
				"ids"		: ({"hei zai", "keeper"}),
				"name"		: "黑仔",
				"title"		: "非洲虎",
				"props"		: ([
					"per"		: 5,
				]),
			]),
			"npc1"		: ([
				"ids"		: ({"ya lang", "guard"}),
				"name"		: "亚郎",
				"title"		: "风雷虎",
				"props"		: ([
					"per"		: 7,
				]),
			]),
			"npc2"		: ([
				"ids"		: ({"dong weiping", "guard"}),
				"name"		: "董伟平",
				"title"		: "深山虎",
				"props"		: ([
					"age"		: 30,
				]),				
			]),
		]),

		"street"	: ([
			"short"		: "崖顶",
			"long"		: "\n山顶树木繁茂苍翠，崖下是寂静幽深的山谷，北面一条小路，蜿蜒\n通向一处山寨。\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/qujing/baoxiang/shanwan1",
			"verb"	: "down",
			"msg1"	: "$N不顾一切地纵身跳下悬崖。",
			"msg2"	: "随着一声惨叫，$N从山顶上滚了下来，如同一滩鼻涕甩在地面。",
		]),

		"arrive"		: ([
			"dst"	: "/d/qujing/baoxiang/shanwan1",
			"verb"	: "climb",
			"msg1"	: "$N挤进岩壁的缝隙，攀着藤条向山上爬去。",
			"msg2"	: "$N从崖下爬了上来，灰头土脸，满山草屑。",
		]),
	]);

	setup();
}

