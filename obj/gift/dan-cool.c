// by firefox 11/12/2010

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"gift";


string eat_msg()
{
	_player->add("bellicosity", -10);
	
	return "$N服下一粒$n，脸上结了一层霜。\n\n";
}

void create()
{
	set_name(HIW"碧水寒丹"NOR, ({"bishui huandan", "handan"}));
	
	set("long", "一粒冒着寒气的丹药，据说由龙宫碧水丹提炼而成。\n\n");
	set("rewards", ([ PEXP : 25*K ]));
	set("eat_msg", (: eat_msg :));

	setup();
}

