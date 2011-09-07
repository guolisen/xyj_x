
#include "config.h"
inherit GROOT"base";

void create()
{
	prop_tab = ([
		"id"		: "nmj",
		"name"		: "鸟鸣涧",
		"color"		: HIG,
		"location"	: "南海紫竹林",
		"slogan"	: "菜鸟乐园",
		
		"guard"		: ([
			"ids"		: ({"cai niao", "niao", "bird"}),
			"name"		: "菜鸟",
			"weapon"	: "/d/obj/weapon/rake/rake",
		]),

		"street"	: ([
			"short"		: "鸟鸣涧",
			"long"		: "\n这是一个鸟语花香的山谷。潺潺清水顺沿山谷飞舞而泻，风拂参天\n古木枝叶如风铃雀跃，置身于这桃源仙境般的令人心醉不已。\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/nanhai/zhulin8",
			"verb"	: "out",
			"msg1"	: "$N扒开紫竹，向外钻去。",
			"msg2"	: "$N很狼狈的从竹林中钻了出来。",
		]),

		"arrive"		: ([
			"dst"	: "/d/nanhai/zhulin8",
			"verb"	: "enter",
			"msg1"	: "$N扒开紫竹，一头钻了进去。",
			"msg2"	: "$N从竹林中钻了进来。",
		]),
	]);
}

