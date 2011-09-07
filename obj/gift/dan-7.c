// by firefox 11/12/2010

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"gift";

//数十年勤修之功
string eat_msg()
{
	_player->add_maximum_force(10);

	return "$N把$n扔进嘴里吞了下去，随即喷出一股浓烟。\n\n";
}


void create()
{
	set_name(RED"七返火丹"NOR, ({"qifan huodan", "huodan" }));

	set("long", "七返丹功参造化，练气之士，得此一粒，可抵数十年勤修之功。\n\n");
	set("rewards", ([ CEXP : 100*K ]));
	set("eat_msg", (: eat_msg :));

	setup();
}

