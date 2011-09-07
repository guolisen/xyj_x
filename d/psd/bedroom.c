// by firefox 02/21/2010

inherit ROOM;

#include <xyj_x.h>

void create()
{
	set("short", "石室");
	set("long", @LONG

阴冷潮湿的山洞，四处可见的石钟乳，遍布的藤蔓，突出一股阴
森诡异的气息。墙边铺着一层稻草。

LONG
		);

	set("objects", ([
		"/d/ourhome/obj/jitui" : 4,
		X_DIR"obj/food/tea" : 2,
	]));
	set("resource", ([ "water" : 1 ]));
	set("valid_startroom", 1);
	set("sleep_room", 1);

	set("exits", ([
		"east"		: __DIR__"cave3",
	]));

	setup();
}
