
#include <ansi.h>

inherit __DIR__"_base";

mapping _guard = ([
	"ids"		: ({"shi wei", "wei", "guard"}),
	"name"		: "侍卫",
	"family"	: "大雪山",
	"weapon"	: "/d/obj/weapon/blade/handudao-blue",
	"props"		: ([]),
]);

void create()
{
	_props = ([
		"id"		: "lushan",
		"name"		: "庐山",
		"color"		: HIC,
		"from"		: "上海站",
		"location"	: "雪山之巅",
		"slogan"	: "不堕不死，奋斗不止！",
		
		"npc"		: ([
			"guard"		: _guard,
			"keeper"	: ([
				"ids"		: ({"guan jia", "keeper"}),
				"name"		: "管家",
				"title"		: "内务总管",
				"props"		: ([
					"age"		: 47,
					"long"		: "一位精明的老管家。\n",
				]),
			]),
			"npc1"		: _guard,
			"npc2"		: _guard,
		]),

		"street"	: ([
			"short"		: HIW"冰崖顶"NOR,
			"long"		: "\n在白雪皑皑的崖顶竟然有一丝暖风，北面冰雪已经渐渐消融，一条\n小路蜿蜒通向一处山寨。\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/xueshan/wroad1",
			"verb"	: "down",
			"msg1"	: "$N脚下一滑，如同落石般滚下冰崖。",
			"msg2"	: "随着一声惨叫，$N从崖顶上滚了下来，在雪地上砸出一个坑。",
		]),

		"arrive"		: ([
			"dst"	: "/d/xueshan/wroad1",
			"verb"	: "climb",
			"msg1"	: "$N攀着冰隙，战战兢兢向冰崖上爬去。",
			"msg2"	: "$N从冰崖下爬了上来，一身霜雪。",
		]),
	]);

	setup();
}
