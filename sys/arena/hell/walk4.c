// by firefox 11/21/2009


inherit ROOM;

void create()
{
	set("short", "幽司");
	set("long", @LONG

这里便是阴曹地府之中，偶尔看到几个索命鬼，勾司人牵着些套着
枷锁的人走来走去。

LONG);

	set("exits", ([
		"east" : __DIR__"room8",
		"west" : __DIR__"room7",
		"north" : __DIR__"walk5",
	]));
	set("hell", 1);
	set("objects", (["/d/death/npc/gousiren" : 1]));

	setup();
}
