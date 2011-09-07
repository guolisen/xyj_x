
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name("双毫笔", ({"bi"}));
	set("weight", 5);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","一只浓墨双毫笔。\n");
		set("unit", "只");
		set("no_get", 1);
		set("no_give", 1);
	}
	set("channel_id", "取经系统");
	setup();
}

