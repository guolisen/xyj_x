// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set ("short", "秦广殿");
	set ("long", @LONG

这里便是阴间地府十王之秦广王的宫殿．平时若是无事，秦广
王便会在殿上处理一些杂务。

LONG);

	set("exits", (["east" : __DIR__"walk5"]));
	set("hell", 1);

	set("objects", ([
		"/d/death/npc/qinguangwang" : 1,
		"/d/death/npc/tong" : 1,
	]));

	setup();
}
