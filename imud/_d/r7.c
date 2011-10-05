// by firefox 04/16/2011
// imud map
inherit ROOM;

#include <imud.h>

void create ()
{
	set ("short", "ÔÆÏ¼¼ä");

	set("exits", ([
		"north"		: __DIR__"r8",
		"south"		: __DIR__"r6",])
	);
	setup();
}

