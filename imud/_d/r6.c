// by firefox 04/16/2011
// imud map
inherit ROOM;

#include <imud.h>

void create ()
{
	set ("short", "»ıÀÆ≈œ");

	set("exits", ([
		"east"		: __DIR__"br",
		"north"		: __DIR__"r7",
		"south"		: __DIR__"r5",])
	);
	setup();
}

