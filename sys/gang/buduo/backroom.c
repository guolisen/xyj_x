// by firefox 02/21/2010

inherit ROOM;

void create ()
{
	set ("short", "密室");
	set ("long", @LONG

一件四面密封不见阳光的暗室，透着阴森诡异的气息。看来这里藏
着帮会的最高机密。

LONG);

	set("exits", ([
		"south" : __DIR__"garden",
	]));
	set("objects", ([
	]));

	setup();
}
