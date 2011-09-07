// by firefox 02/21/2010

inherit ROOM;

#include <ansi.h>

void create()
{
	set("short", "白骨洞");
	set("long", "\n\n"
"阴冷潮湿的山洞，四处可见的石钟乳，遍布的藤蔓，突出一股阴\n"
"森诡异的气息。四壁上"HIB BLINK"磷光"NOR"点点，忽明忽灭。\n\n"
	);
	set("exits", ([
		"south"		: __DIR__"cave3",
	]));

	set("objects", ([ __DIR__"npc/bai" : 1 ]) );

	setup();
}

