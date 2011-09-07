// by firefox 02/21/2010

#include <ansi.h>

inherit ROOM;

void create ()
{
	set ("short", "柴房");
	set ("long", @LONG

这是一间柴房，里面堆满了柴草，枯枝，还有一些杂物凌乱的扔
在四处。

LONG);

	set("exits", ([
		"west" : __DIR__"backyard",
	]));


	setup();
}
