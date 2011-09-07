// by firefox 02/21/2010

#include <ansi.h>

inherit ROOM;

void create ()
{
	set ("short", "兽栏");
	set ("long", @LONG

这是一间坚固而且宽敞的兽栏，如果在这里驯养各种珍禽野兽，一
定是个好地方。

LONG);

	set("exits", ([
		"west" : __DIR__"garden",
	]));

	setup();
}
