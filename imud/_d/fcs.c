// by firefox 04/16/2011
// imud map
inherit ROOM;

#include <imud.h>

void create()
{
	set("short", "Ò»ÖÀÇ§½ð");
	set("exits", ([
		"east"		: iFCS_DIR "stand0",
		"south"		: iFCS_DIR "stand1",
		"west"		: __DIR__ "r2",
		"north"		: iFCS_DIR "stand3",])
	);

	setup();
}
