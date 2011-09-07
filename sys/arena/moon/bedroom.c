// by firefox 11/21/2009

#include <ansi.h>
inherit ROOM;

void create ()
{
	set ("short", "卧房");
	set ("long", @LONG

一间淡湖绿色的房间, 三面是书架, 上面摆满了杂七杂八的书，对湖的一
面开了一扇竹窗, 窗前放着一架五弦琴，墙边有一张牙玉色的软榻。

LONG);
	
	set("exits", ([
		"down" : __DIR__"rain",
	]));

	setup();
}
