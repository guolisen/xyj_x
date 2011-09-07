// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;
inherit F_CMD;
inherit F_LOADABLE;

void create()
{
	set_name(HIG"命令宝珠"NOR, ({ "command pearl", "pearl" }) );
	set("long", "一颗光芒四射的宝珠，可以让你测试沙盒技能。\n");
	set("unit", "颗" );
	set("changed", 1);
}

void init()
{
	filter_cmd();
}
