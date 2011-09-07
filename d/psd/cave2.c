// by firefox 02/21/2010

inherit ROOM;


void create()
{
	set("short", "洞内");
	set("long", @LONG

阴冷潮湿的山洞，四处可见的石钟乳，遍布的藤蔓，突出一股阴
森诡异的气息。

LONG
		);

	set("exits", ([
		"south"		: __DIR__"cave1",
		"north"		: __DIR__"center",
	]));

	setup();
}

