// by firefox 02/21/2010

#include <ansi.h>

inherit ROOM;
void create ()
{
	set ("short", "厢房");
	set ("long", @LONG

这是一件雅致的客房。屋角香炉里传来一阵阵清香。一张宽大柔软
的床上铺着被褥，让人不觉昏昏欲睡。

LONG);

	set("exits", ([
		"west" : __DIR__"parlor",
	]));

	set("objects", ([
		__DIR__"_keeper" : 1,
	]));

	setup();
}
