inherit "/d/sldh2/guild/base";

#include "config.h"

void create()
{
	prop_tab = ([
		"id"            : "mllz",
		"name"          : "没落龙族",
		"color"         : HIB,
		"location"      : "东海毒龙岛",
		"slogan"        : "助人为乐，开心你我",

		"guard"         : ([
			"ids"           : ({"xiaoqing long", "long", "dragon"}),
			"name"          : "小青龙",
			"weapon"        : "/d/obj/weapon/axe/bigaxe",
		]),

		"street"        : ([
			"short"         : "毒龙岛",
			"long"          : "\n这里碧水环绕，芳草萋萋，绿叶盈枝，鸟雀齐鸣，流水叮咚，清泉\n飞瀑，构成一幅万簌俱唱，繁花盈野的景象。\n\n",
		]),

		"leave"         : ([
			"dst"   : "/d/sea/maze0",
			"verb"  : "down",
			"msg1"  : "$N扑通一声跳下水。",
			"msg2"  : "$N突然出现在水底。",
		]),

		"arrive"                : ([
			"dst"   : "/d/sea/maze0",
			"verb"  : "swim",
			"msg1"  : "$N向水面游去。",
			"msg2"  : "$N从水中露出头来。",
		]),
	]);
}
