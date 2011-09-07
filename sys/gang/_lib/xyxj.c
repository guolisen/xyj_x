inherit "/d/sldh2/guild/base";

#include "config.h"

void create()
{
	prop_tab = ([
		"id"            : "xyxj",
		"name"          : "逍遥仙界",
		"color"         : HIM,
		"location"      : "蓬莱仙阁",
		"slogan"        : "开心游戏 快乐聊天",

		"guard"         : ([
			"ids"           : ({"xian tong", "tong", "guard"}),
			"name"          : "仙童",
			"weapon"        : "/d/obj/weapon/sword/qingfeng",
		]),

		"street"        : ([
			"short"         : "石洞中",
			"long"          : "\n洞中很明亮，钻出去是百丈悬崖，北面则豁然开朗，像是一处与世\n隔绝的世外桃源。\n\n",
		]),

		"leave"         : ([
			"dst"   : "/d/penglai/road1",
			"verb"  : "out",
			"msg1"  : "$N从洞中向一处小缝隙挤了进去。",
			"msg2"  : "$N从崖壁上的一处缝隙中艰难的挤了出来",
		]),

		"arrive"                : ([
			"dst"   : "/d/penglai/road1",
			"verb"  : "enter",
			"msg1"  : "$N钻进崖壁上的一处小缝隙。",
			"msg2"  : "$N艰难的挤进了石洞。",
		]),
	]);
}
