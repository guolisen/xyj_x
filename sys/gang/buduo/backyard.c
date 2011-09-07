// by firefox 02/21/2010

inherit ROOM;

void create ()
{
	set ("short", "后院");
	set ("long", @LONG

后院方方正正，空空荡荡，落叶遍地，也没有人打扫。北面飘来
一阵阵花香。

LONG);

	set("outdoors", 1);
	set("exits", ([
		"south" : __DIR__"parlor",
		"north" : __DIR__"garden",
		"east" : __DIR__"z2",
		"west" : __DIR__"kitchen",
	]));

	setup();
}
