// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set("short", "楚江殿");
	set("long", @LONG

这里便是阴间地府十王之初江王的宫殿．平时若是无事，初江
王便会在殿上处理一些杂务。

LONG);

	set("exits", (["west" : __DIR__"walk4"]));
	set("hell", 1);
	set("objects", ([
		"/d/death/npc/chujiangwang" : 1,
		"/d/death/npc/tong" : 1,
	]));

	setup();
}
