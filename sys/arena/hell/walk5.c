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
		"south" : __DIR__"walk4",
		"west" : __DIR__"room9",
		"north" : __DIR__"walk6",
	]));
	set("hell", 1);

	setup();
}
