// by firefox 11/21/2009
// ����

inherit NPC;

#include "_base.h"

void create()
{
	set_name("����", ({"pet"}));
	set("race", "Ұ��");
	set("age", 10);

}

void init_var()
{
	_subs = ([
		"������"		: ([
			"ids"			: ({"mink"}),
		]),
		"Х��Ȯ"		: ([
			"ids"			: ({"dog"}),
		]),
	]);
}

