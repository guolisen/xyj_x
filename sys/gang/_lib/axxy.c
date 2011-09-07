inherit "/d/sldh2/guild/base";

#include "config.h"

void create()
{
	prop_tab = ([
		"id"            : "axxy",
		"name"          : "翱翔西游",
		"color"         : HIR,
		"location"      : "终南山",
		"slogan"        : "互助，共享，黑帮",

		"guard"         : ([
			"ids"           : ({"kanmen ren", "ren", "guard"}),
			"name"          : "看门人",
			"weapon"        : "/d/obj/weapon/axe/bigaxe",
		]),

		"street"        : ([
			"short"         : "崖顶",
			"long"          : "\n山顶树木繁茂苍翠，崖下是寂静幽深的山谷，北面一条小路，蜿蜒\n通向一处山寨。\n\n",
		]),

		"leave"         : ([
			"dst"   : "/d/changan/zhongnan",
			"verb"  : "down",
			"msg1"  : "$N不顾一切地纵身跳下悬崖。",
			"msg2"  : "随着一声惨叫，$N从山顶上滚了下来，如同一滩鼻涕甩在地面。",
		]),

		"arrive"                : ([
			"dst"   : "/d/changan/zhongnan",
			"verb"  : "climb",
			"msg1"  : "$N攀着藤条，向山崖上爬去。",
			"msg2"  : "$N从崖下爬了上来，灰头土脸，满山草屑。",
		]),
	]);
}
