// by firefox 04/16/2011
// imud map
inherit ROOM;

#include <imud.h>

void create ()
{
	set ("short", "å«º£±ß");

	set("exits", ([
		"south"		: __DIR__"r9",])
	);
	setup();
}

