// by firefox 02/21/2010

inherit ROOM;
#include "_config.h"
#include "_stop_mx.h"

void create()
{
	set("short", "山寨门");
	set("long", "\n"
		"这里是一处很大的山寨。深沟高墙，鹿角密布，寨门敞开。一面大\n"
		"旗迎风飘扬，上书几个大字：『" + GANG_NAME + "』\n\n"
	);
	set("exits", ([
		"south"		: __DIR__"street",
		"north"		: __DIR__"yard",
	]));

	set("objects", ([
		__DIR__"_guard" : 2,
	]));

	set("outdoors", 1);

	setup();
}

