// by firefox 11/12/2010

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"gift";

string eat_msg()
{
	_player->add("food", 20);				//发汗

	return "$N拿起$n狼吞虎咽地吃起来，直吃得满嘴流油。\n\n";
}


void create()
{
	set_name(RED"蒸肉"NOR, ({"zheng rou", "meat"}));

	set("unit","块");
	set("long","一块肥肥嫩嫩的蒸肉，不是取自珍禽,也不是取自猛兽，而是取经人。\n");
	set("rewards", ([ DEXP : 20*K, PEXP : 20*K ]));
	set("eat_msg", (: eat_msg :));

	setup();
}

