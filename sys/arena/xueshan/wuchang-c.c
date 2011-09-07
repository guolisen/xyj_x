// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set ("short", "中心武场");
	set ("long", @LONG

这是冰宫前的一块平地，供大雪山弟子练功之用。冰面极平，光
鉴照人。不过走在上面得小心点，雪山弟子也正是借此锻炼下盘
的稳固功夫。

LONG);

	set("exits", ([
		"south" : __DIR__"wuchang-s",
		"north" : __DIR__"wuchang-n",
		"west" : __DIR__"wuchang-w",
		"east" : __DIR__"wuchang-e",
	]));
	
	set("objects", ([
		"/d/xueshan/npc/xunshi" : 2,
		"/d/xueshan/npc/yingwu-guai" : 1,
		"/d/obj/misc/ice.c" : 1,
	]));

	set("outdoors", "xueshan");

	setup();
}

