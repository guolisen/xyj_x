// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set("short", "西北武场");
	set("long", @LONG

这是冰宫前的一块平地，供大雪山弟子练功之用。冰面极平，光
鉴照人。不过走在上面得小心点，雪山弟子也正是借此锻炼下盘
的稳固功夫。东面的一栋房子顶上一股炊烟冉冉升起，想必是厨
房了。

LONG);

	set("exits", ([
		"south" : __DIR__"wuchang-w",
		"east" : __DIR__"wuchang-n",
	]));
	
	set("objects", ([
		"/d/obj/misc/ice" : 2,
	]));
	set("outdoors", "xueshan");

	setup();
}
