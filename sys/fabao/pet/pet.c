// by firefox 11/21/2009
// ³èÎï

inherit NPC;

#include "_base.h"

void create()
{
	set_name("³èÎï", ({"pet"}));
	set("race", "Ò°ÊŞ");
	set("age", 10);

}

void init_var()
{
	_subs = ([
		"»¨ºüõõ"		: ([
			"ids"			: ({"mink"}),
		]),
		"Ğ¥ÌìÈ®"		: ([
			"ids"			: ({"dog"}),
		]),
	]);
}

