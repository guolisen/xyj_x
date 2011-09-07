// by firefox 14/06/2009 

#include <ansi.h>

inherit ITEM;

#define NAME	HIM"蟠桃"NOR
#define ID		"pan tao"

void create()
{
	set_name( NAME , ({ ID }));
	set_weight(90);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "颗");
		set("long", "\n"
			"半红半绿喷甘香，艳丽仙根万载长。堪笑武陵源上种，争如天府更奇强！\n"
			"紫纹娇嫩寰中少，缃核清甜世莫双。延寿延年能易体，有缘食者自非常。\n\n"
		);

		set("value", 100000);
		set("drug_type", "补品");
	}
	setup();
}

void init()
{
	add_action("do_eat", "eat");	
}

int do_eat(string arg)
{
	object who = this_player();
//增加寿命
	
	message_vision(HIG"$N吞下一颗"NAME HIG"，顿觉脱胎换骨。\n" NOR, who);

	
	destruct(this_object());
	return 1;
}
