// by firefox 04/16/2011
// imud map
inherit ROOM;

#include <imud.h>

void create ()
{
	set ("short", "Çó²Æ½Ö");

	set("exits", ([
		"north"		: __DIR__"r2",
		"south"		: __DIR__"r0",])
	);
	setup();
}

