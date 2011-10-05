// by firefox 04/16/2011
// imud map
inherit ROOM;

#include <imud.h>

void create ()
{
	set ("short", "Çó²Æ½Ö");

	set("exits", ([
		"east"		: __DIR__"fcs",
		"north"		: __DIR__"r3",
		"south"		: __DIR__"r1",])
	);
	setup();
}

