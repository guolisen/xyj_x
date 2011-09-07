// by firefox 02/21/2010

inherit ROOM;

void create ()
{
	set ("short", "正院");
	set ("long", @LONG

四周杨柳婆娑，中间空阔的场地上铺满了细细的黄土，适合演武。

LONG);

	set("outdoors", 1);
	set("exits", ([
		"south" : __DIR__"gate",
		"north" : __DIR__"parlor",
		"east" : __DIR__"study",
		"west" : __DIR__"practice",
	]));

	setup();
}
