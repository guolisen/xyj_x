
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "灵霄宝殿");
	set("long", @LONG

todo:需要描述信息。

LONG );

	set("exits", ([
		"south"   : __DIR__"lingxiao",
		"north"   : __DIR__"lingxiao",
		"west"   : __DIR__"lingxiao",
		"east"   : __DIR__"lingxiao",
	]));


	set("objects", ([
		__DIR__"anuo"   : 1,
		__DIR__"jiaye"   : 1,
		__DIR__"rulai"   : 1,
	]));

	setup();
}

void init()
{	
	//add_action("do_sa",  "sa");
}

int valid_leave(object me, string dir)
{
	return notify_fail("你刚想溜，被迦叶尊者挡住了去路。\n");
}
