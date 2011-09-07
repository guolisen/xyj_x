// by firefox 02/21/2010

inherit ROOM;

#include <room.h>
#include "_config.h"
#include <ansi.h>

#define ARROW		"/d/obj/weapon/archery/zhujian"

void create ()
{
	set ("short", "憩园");
	set ("long", @LONG

一片静静的园林，真是供人休息的佳处。中间一个小水塘，清风
拂过，波光点点。墙上一首诗：

    城上斜阳画角哀，沈园非复旧池台。
    伤心桥下春波绿，曾是惊鸿照影来。

LONG);

	set("resource", ([ "water": 1 ]) );
	set("outdoors", 1);
	set("exits", ([
		"south" : __DIR__"backyard",
		"north" : __DIR__"backroom",
		"east" : __DIR__"animal",
		"west" : __DIR__"medicine",
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	if(dir == "north" && !G->is_executive(me)) {
		object arrows = new(ARROW);
		arrows->set_amount(3 + random(5));
		arrows->move(this_object());
		message_vision(HIW"$N往北走去，突然屋内乱箭齐发，$N急退躲过，惊出一身冷汗。\n\n"NOR, me);
		if(!me->is_busy()) me->start_busy(20);
		me->command("sweat");
		return notify_fail("\n");
	}
	return ::valid_leave(me, dir);
}

