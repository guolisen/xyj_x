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

	set("if_bed", 1);
	set("sleep_room", 1);

	set("no_fight", 1);
	set("no_magic", 1);
	
	set("valid_startroom", 1);
	set("no_upgrade_age", 1);

	set("exits", ([
		"east" : __DIR__"parlor",
	]));
	
	setup();

	call_other(__DIR__"board", "???");
}
