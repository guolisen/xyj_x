// by firefox 04/16/2011
// imud map
inherit ROOM;

#include <imud.h>

void create ()
{
	set ("short", "嫺���");

	set("exits", ([
		"south"		: __DIR__"r9",])
	);
	setup();
}

