
#include <ansi.h>

inherit __DIR__"_base";

void create()
{
	_props = ([
		"id"		: "huisuo",
		"name"		: "私人会所",
		"color"		: HIB,
		"from"		: "-",
		"location"	: "长乐乐坊",
		"slogan"	: "吃喝嫖赌 挥金如土。",
		
		"npc"		: ([
			"guard"		: ([
				"ids"		: ({"bao an", "guard"}),
				"name"		: "保安",
				"family"	: "将军府",
				"weapon"	: "/d/obj/weapon/axe/bigaxe",				
				"props"		: ([ "gender" : "男性" ]),
			]),
			"keeper"	: ([
				"ids"		: ({"wu shi", "keeper"}),
				"name"		: "无事",
				"title"		: "管家",
				"props"		: ([
					"age"		: 50,
					"per"		: 5,
				]),
			]),
			"npc1"		: ([
				"ids"		: ({"yingbin xiaojie", "girl", "guard"}),
				"name"		: "迎宾小姐",
				"props"		: ([
					"age"		: 20,
					"per"		: 30,
					"gender"	: "女性",
					"block_msg"	: "$N拦住$n说道：客官请止步。\n",
				]),
			]),
			"npc2"		: ([
				"ids"		: ({"anmo nvlang", "girl", "guard"}),
				"name"		: "按摩女郎",
				"props"		: ([
					"age"		: 18,
					"gender"	: "女性",

					"block_msg"	: "$N拦住$n说道：客官请止步。\n",
				]),				
			]),
		]),

		"street"	: ([
			"short"		: "小巷",
			"long"		: "\n小巷光线昏暗，蜿蜒通向一处小院。\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/city/club",
			"verb"	: "out",
			"msg1"	: "$N推动暗门，钻了出去。",
			"msg2"	: "墙角出现一道暗门，$N钻了出来，随即暗门也消失了。",
		]),

		"arrive"		: ([
			"dst"	: "/d/city/club",
			"verb"	: "enter",
			"msg1"	: "$N按动机关，钻进一道暗门，随即暗门也消失了。",
			"msg2"	: "$N从暗门外钻了进来。",
		]),
	]);

	setup();
}

