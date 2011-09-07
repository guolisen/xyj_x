// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set("short", "幽司");
	set("long", @LONG

这是一条长长的厢廊，没有什么人走动。周围也没有什么动静，一切
都是静悄悄的。北面有一座青紫砖石的宫殿，笼在一股青烟之中。

LONG);

	set("exits", ([
		"south" : __DIR__"walk5",
		"northup" : __DIR__"cuiyun",
	]));
	set("hell", 1);

	set("objects", ([
		"/d/death/npc/tong2" : 1,
		"/d/death/npc/tong1" : 1,
	]));

	setup();
}

