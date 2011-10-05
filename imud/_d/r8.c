// by firefox 04/16/2011
// imud map
inherit ROOM;

#include <imud.h>

void create ()
{
	set ("short", "ÔÆÏ¼¼ä");

	set("exits", ([
		"west"		: __DIR__"jack",
		"north"		: __DIR__"r9",
		"south"		: __DIR__"r7",])
	);
	setup();
}

