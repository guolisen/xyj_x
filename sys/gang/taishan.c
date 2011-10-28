
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
		"id"		: "taishan",
		"name"		: "泰山",
		"color"		: HIG,
		"from"		: "北京站",
		"location"	: "开封城",
		"slogan"	: "会当凌绝顶，一览众山小。",
		
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
			"long"		: "\n这是一条直通天蓬府和开封郊外的秘道。北面就是出口，隐约有条\n小路，蜿蜒通向一处山寨。\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/kaifeng/shuaifu",
			"verb"	: "out",
			"msg1"	: "$N推动暗门，向外爬去。",
			"msg2"	: "墙角出现一道暗门，$N爬了出来，随即暗门也消失了。",
		]),

		"arrive"		: ([
			"dst"	: "/d/kaifeng/shuaifu",
			"verb"	: "enter",
			"msg1"	: "$N按动机关，钻进一道暗门，随即暗门也消失了。",
			"msg2"	: "$N从暗门外钻了进来。",
		]),
	]);

	setup();
}
