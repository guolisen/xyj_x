
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name("˫����", ({"bi"}));
	set("weight", 5);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","һֻŨī˫���ʡ�\n");
		set("unit", "ֻ");
		set("no_get", 1);
		set("no_give", 1);
	}
	set("channel_id", "ȡ��ϵͳ");
	setup();
}

