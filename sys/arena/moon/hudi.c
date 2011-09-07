// by firefox 11/21/2009

#include <ansi.h>

inherit ROOM;

void create ()
{
	set ("short", "湖底");
	set ("long", @LONG

到了湖底你才明白＂莲出淤泥而不染＂的真正含义．
LONG);
	set("exits", ([
		"up" : __DIR__"lotuspond",
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	message_vision(CYN"$N拼命挣扎着爬上岸，肚子里灌满了水．\n"NOR, me);
	me->set("water", (int)me->max_water_capacity());
	return ::valid_leave(me, dir);
}
