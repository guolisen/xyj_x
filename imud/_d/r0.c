// by firefox 04/16/2011
// imud map
inherit ROOM;

#include <imud.h>

void create ()
{
	set ("short", "�޾����");

	set("exits", ([
		"north"		: __DIR__"r1",
		"out"		: "/d/ourhome/honglou/bull"])
	);
	setup();
}

