
#include <ansi.h>

inherit __DIR__"_base";

mapping _guard = ([
	"ids"		: ({"huo qilin", "qilin", "guard"}),
	"name"		: "火麒麟",
	"family"	: "火云洞",
	"weapon"	: "/d/obj/weapon/rake/rake",
	"props"		: ([]),
]);

void create()
{
	_props = ([
		"id"		: "buduo",
		"name"		: "不堕轮回教",
		"color"		: HIY,
		"location"	: "火焰山",
		"slogan"	: "天上地下，唯我独尊！",
		
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
			"short"		: "烟消谷",
			"long"		: "\n这是火焰山上的一条峡谷，石壁上都是烟熏火燎的痕迹，北面有条\n小路，蜿蜒通向一处山寨。\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/qujing/firemount/nofire",
			"verb"	: "up",
			"msg1"	: "$N你奋力向山上爬去。",
			"msg2"	: "$N气喘吁吁的爬了上来。",
		]),

		"arrive"		: ([
			"dst"	: "/d/qujing/firemount/nofire",
			"verb"	: "jump",
			"msg1"	: "$N纵身一跃，跳下山谷。",
			"msg2"	: "一声闷响，$N趴在地上一动不动。",
		]),
	]);

	setup();
}
