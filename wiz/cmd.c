// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit ITEM;
inherit F_CMD;
inherit F_LOADABLE;

void create()
{
	set_name(HIG"�����"NOR, ({ "command pearl", "pearl" }) );
	set("long", "һ�Ź�â����ı��飬�����������ɳ�м��ܡ�\n");
	set("unit", "��" );
	set("changed", 1);
}

void init()
{
	filter_cmd();
}
