// by firefox 02/21/2010

inherit ROOM;

#include "_config.h"
#include <ansi.h>

mapping _leave = G->query("leave");

void create()
{
	mapping m = G->query("street");
	set("short", m["short"]);
	set("long", m["long"]);
	set("exits", ([ /* sizeof() == 2 */
		_leave["verb"]	: _leave["dst"],
		"north"			: __DIR__"gate",
	]));

	set("out_doors", 1);

	setup();
}


int valid_leave(object me, string dir)
{
	if(dir == _leave["verb"]) {
		message_vision(HIC + _leave["msg1"] + "\n\n"NOR, me);
		me->move(_leave["dst"]);
		if(!me->is_busy()) me->start_busy(3);
		message_vision(HIC"\n" + _leave["msg2"] + "\n"NOR, me);
		return notify_fail("\n");
	}
	return 1;
}

