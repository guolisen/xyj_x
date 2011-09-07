// by firefox 02/21/2010

inherit ROOM;

void create()
{
	set("short", "碧池");
	set("long", @LONG

阴冷潮湿的山洞，四处可见的石钟乳，遍布的藤蔓，突出一股阴
森诡异的气息。中间一个浅浅的水池，碧水荡漾，波光粼粼。

LONG
		);
	set("resource", ([ "water" : 1 ]));
	set("exits", ([
		"south"		: __DIR__"cave5",
		"north"		: __DIR__"xiaroom",
		"west"		: __DIR__"cave-w",
		"east"		: __DIR__"cave-e",
	]));

	setup();
}

