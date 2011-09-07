// by firefox 11/12/2010

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"gift";

//菩提花入药有发汗解热、镇痛之效
string eat_msg()
{
	_player->add("water", -100);				//发汗
	_player->receive_curing("kee", 1000);	//镇痛
	_player->receive_heal("kee", 1000);

	return "$N把$n放在嘴里嚼烂咽了下去，只感到灵台处无比的清净舒畅。\n\n";
}


void create()
{
	set_name(HIC"菩提花"NOR, ({"puti flower", "puti", "flower"}));

	set("unit","朵");
	set("long","菩提花生于菩提树叶腋，难见真面目，称隐头花序成对腋生。\n");
	set("rewards", ([ DEXP : 20*K, PEXP : 20*K ]));
	set("eat_msg", (: eat_msg :));

	setup();
}

