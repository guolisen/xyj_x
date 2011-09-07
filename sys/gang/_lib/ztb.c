
#include "config.h"
inherit GROOT"base";

void create()
{
	prop_tab = ([
		"id"		: "ztb",
		"name"		: "猪头帮",
		"color"		: HIM,
		"location"	: "开封天蓬府",
		"slogan"	: "猪头不帅，活的精彩",
		
		"guard"		: ([
			"ids"		: ({"lao muzhu", "muzhu", "zhu", "pig"}),
			"name"		: "老母猪",
			"weapon"	: "/d/obj/weapon/rake/rake",
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
}

