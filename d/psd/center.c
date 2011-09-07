// by firefox 02/21/2010

inherit ROOM;


void create()
{
	set("short", "洞中");
	set("long", @LONG

阴冷潮湿的山洞，四处可见的石钟乳，遍布的藤蔓，突出一股阴
森诡异的气息。这里渐渐宽敞，可容纳数十人。

LONG
		);

	set("exits", ([
		"south"		: __DIR__"cave2",
		"west"		: __DIR__"cave3",
		"east"		: __DIR__"cave4",
		"north"		: __DIR__"cave5",
	]));

	setup();
}
