// by firefox 11/21/2009

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
	set("short", "听雨楼顶");
	set("long", @LONG

这里就是听雨楼顶。脚下是碧玉瓦，南面是莲花池。东边路对面就是噙芳
阁。一眼望去，美景尽收眼底。

LONG);
	
	setup();
}
