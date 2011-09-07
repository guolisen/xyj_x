// by firefox 02/21/2010

inherit ROOM;
#include <xyj_x.h>

void create ()
{
	set ("short", "丹房");
	set ("long", @LONG

只是一间炼丹房，墙角焚着一炉檀香，一丝若有若无的幽香满室缭
绕。让整个房间透着朦胧和神秘。

LONG);

	set("exits", ([
		"east" : __DIR__"garden",
	]));

	set("objects", ([
		//GANG_DIR"_lib/danlu"	: 1,
	]));

	setup();
}
