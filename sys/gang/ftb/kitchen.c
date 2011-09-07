// by firefox 02/21/2010

inherit ROOM;

#include <xyj_x.h>

void create ()
{
	set ("short", "厨房");
	set ("long", @LONG

厨房里打扫的很干净。几口大锅里冒出阵阵香气，令人垂涎欲滴。

LONG);

	set("resource", ([ "water": 1 ]) );

	set("exits", ([
		"east" : __DIR__"backyard",
	]));

	set("objects", ([
		X_DIR"obj/food/tea"		: 1,
		"/d/lingtai/obj/baozi"	: 3,
	]));

	setup();
}
