// by firefox 04/16/2011
// imud map
inherit ROOM;

#include <imud.h>

void create ()
{
	set ("short", "È¡¾­Â·");

	set("exits", ([
		"west"		: __DIR__"xys",
		"north"		: __DIR__"r5",
		"south"		: __DIR__"r3",])
	);
	setup();
}

