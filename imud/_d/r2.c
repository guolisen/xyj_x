// by firefox 04/16/2011
// imud map
inherit ROOM;

#include <imud.h>

void create ()
{
	set ("short", "��ƽ�");

	set("exits", ([
		"east"		: __DIR__"fcs",
		"north"		: __DIR__"r3",
		"south"		: __DIR__"r1",])
	);
	setup();
}

