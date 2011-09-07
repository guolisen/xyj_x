// by firefox 11/21/2009

inherit "/d/sldh2/feature/whistle";

#include <ansi.h>

mixed* tab = ({
	({ HIR"千里一盏灯",	"一匹通体亮红的骏马。" }),
	({ HIC"赛龙五斑驹",	"一匹满身斑点的骏马。" }),
	({ HIB"没角癞麒麟",	"一匹满身疙瘩的骏马。" }),
	({ HIW"踏乌白雪马",	"一匹通体雪白的骏马。" }),
	({ HIY"金睛兽",		"一匹眼露金光的骏马。" }),
	({ HIR"赤炭火龙驹",	"一匹通体火红的骏马。" }),
	({ HIY"黄骠透骨龙", "一匹骁勇矫健的战马，通体橙黄，毛无杂色。" }),
});


void create()
{
	string* msg = random_1(tab);

	::create();

	ctor("/d/sldh2/feature/horse", ([
		"name"		: msg[0] + NOR,
		"long"		: msg[1],
		"come"		: "一声长嘶，$n从滚滚烟尘中疾驰而来。",
		"leave"		: "一声长嘶，$N绝尘而去。",
	]));
}
