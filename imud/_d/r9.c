// by firefox 04/16/2011
// imud map
inherit ROOM;

#include <imud.h>

void create ()
{
	set ("short", "嫺���");

	set("exits", ([
		"north"		: __DIR__"r10",
		"south"		: __DIR__"r8",])
	);
	setup();
}

