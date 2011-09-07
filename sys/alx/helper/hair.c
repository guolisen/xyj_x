// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY"救命毫毛"NOR, ({ "hair" }) );
	set_weight(10);

	set("long", "一根救命毫毛，危急时刻用来(use)救命。\n");
	set("unit", "根");

	set("no_get", 1);
	set("no_put", 1);
	set("no_give", 1);

	setup();
}

int init ()  
{   
	object who = _player;
	add_action ("do_use", "use");

	if(environment() == who) {
		msv(CYN"\n一片杨柳叶儿缓缓飘入$N怀中，化作一根毫毛。\n"NOR, who);
		tell_object(who, CYN
			"冥冥中传来一个声音：\n\n"HIY
			"    『若到那无济无主的时节，可以随机应变，救得你急苦之灾。』\n\n"NOR);
		trace(getuid(who) + "得到救命毫毛。", D_WIZ);
	}
	return 1;
}

int do_use (string arg)
{
	if(arg != "hair") return 0;	
	ALX->help_me(_player);
	destruct(_this);
	return 1;
}
