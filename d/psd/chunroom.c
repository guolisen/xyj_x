// by firefox 02/21/2010

inherit ROOM;

#include <ansi.h>

void create()
{
	set("short", "桃花阁");
	set("long", "\n\n"
"阴冷潮湿的山洞，四处可见的石钟乳，遍布的藤蔓，突出一股阴\n"
"森诡异的气息。墙上斜插几枝"HIM"桃花"NOR"，四周挂满蜘蛛网。\n\n"
	);

	set("exits", ([
		"south"		: __DIR__"cave4",
	]));

	set("objects", ([ __DIR__"npc/chun" : 1 ]) );

	setup();
}

