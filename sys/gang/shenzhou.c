
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
		"id"		: "shenzhou",
		"name"		: "神州",
		"color"		: HIR,
		"from"		: "北京站",
		"location"	: "长安城",
		"slogan"	: "神州大地，遍插红旗。",
		
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
			"short"		: "秘道",
			"long"		: "\n这是一条直通三花堂和长安郊外的秘道。北面就是出口，隐约有条\n小路，蜿蜒通向一处山寨。\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/city/sanhua-mishi",
			"verb"	: "out",
			"msg1"	: "$N推动暗门，向外爬去。",
			"msg2"	: "墙角出现一道暗门，$N爬了出来，随即暗门也消失了。",
		]),

		"arrive"		: ([
			"dst"	: "/d/city/sanhua-mishi",
			"verb"	: "enter",
			"msg1"	: "$N按动机关，钻进一道暗门，随即暗门也消失了。",
			"msg2"	: "$N从暗门外钻了进来。",
		]),
	]);

	setup();
}
