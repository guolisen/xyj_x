// by firefox 04/16/2011
// imud map
inherit ROOM;

#include <imud.h>

void create ()
{
	set ("short", "ÈõË®ÅÏ");

	set("exits", ([
		"north"		: __DIR__"r6",
		"south"		: __DIR__"r4",])
	);
	setup();
}

