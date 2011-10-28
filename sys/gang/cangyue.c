
#include <ansi.h>

inherit __DIR__"_base";

void create()
{
	_props = ([
		"id"		: "cangyue",
		"name"		: "苍月",
		"color"		: HIC,
		"from"		: "小雨西游",
		"location"	: "清凉谷",
		"slogan"	: "逍遥自在，聊天打诨！",
		
		"npc"		: ([
			"guard"		: ([
				"ids"		: ({"yin shi", "guard"}),
				"name"		: "隐士",
				"title"		: "小雨流浪汉",
				"family"	: "阎罗地府",
				"weapon"	: "/d/qujing/qinglong/obj/stick",		
				"props"		: ([]),
			]),
			"keeper"	: ([
				"ids"		: ({"xiaoyao shu", "keeper"}),
				"name"		: "逍遥鼠",
				"title"		: "小雨管家",
				"props"		: ([
					"age"		: 47,
					"per"		: 5,
				]),
			]),			
			"npc1"		: ([
				"ids"		: ({"bai qi", "guard"}),
				"name"		: "绝世白起",
				"title"		: "小雨杀人狂",
				"props"		: ([
				]),
			]),
			"npc2"		: ([
				"ids"		: ({"hua bianque", "guard"}),
				"name"		: "华扁鹊",
				"title"		: "小雨郎中",
				"props"		: ([
				]),				
			]),
		]),

		"street"	: ([
			"short"		: "崖顶",
			"long"		: "\n山顶树木繁茂苍翠，崖下是寂静幽深的山谷，北面一条小路，蜿蜒\n通向一处山寨。\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/southern/wutai/qinglianggu",
			"verb"	: "down",
			"msg1"	: "$N不顾一切地纵身跳下悬崖。",
			"msg2"	: "随着一声惨叫，$N从山顶上滚了下来，如同一滩鼻涕甩在地面。",
		]),

		"arrive"		: ([
			"dst"	: "/d/southern/wutai/qinglianggu",
			"verb"	: "climb",
			"msg1"	: "$N攀着藤条，向山崖上爬去。",
			"msg2"	: "$N从崖下爬了上来，灰头土脸，满山草屑。",
		]),
	]);

	setup();
}

