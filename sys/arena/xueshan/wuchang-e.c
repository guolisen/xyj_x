// by firefox 11/21/2009

inherit ROOM;

void create ()
{
	set ("short", "东武场");
	set ("long", @LONG

这是冰宫前的一块平地，供大雪山弟子练功之用。冰面极平，光
鉴照人。不过走在上面得小心点，雪山弟子也正是借此锻炼下盘
的稳固功夫。
LONG);

	set("exits", ([
		"south" : __DIR__"wuchang-se",
		"north" : __DIR__"wuchang-ne",
		"west" : __DIR__"wuchang-c",
	]));
	
	set("objects", ([
		"/d/xueshan/npc/tuying-zunzhe" : 1,
        "/d/xueshan/npc/baixiang-zunzhe" : 1,
	]));

	set("outdoors", "xueshan");

	setup();
}

