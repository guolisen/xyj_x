// by firefox 11/21/2009

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
	set ("short", "听雨楼");
	set ("long", @LONG

一座两层的碧绿色小竹楼, 三面环水, 窗外一泓秋水，池边花树映水而红
，灿若云霞；池中零，残荷点点。一方平台傍水而建，白石为栏，碧玉为
砖。台面晶莹剔透，平整如镜，隐隐有红光流动。

LONG);

	set("exits", ([
		"east"		: __DIR__"road3",
		"south"		: __DIR__"lotuspond",
		"up"		: __DIR__"bedroom",
	]));
	
	setup();
}
