// by firefox 04/16/2011
// imud map
inherit ROOM;

#include <imud.h>

void create ()
{
	set ("short", "È¡¾­Â·");

	set("exits", ([
		"north"		: __DIR__"r4",
		"south"		: __DIR__"r2",])
	);
	setup();
}

