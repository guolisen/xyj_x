// by firefox 11/21/2009

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set ("short", "后院");
	set ("long", @LONG

后院里落叶遍地，也没有人打扫。角落里有一口石井，上面长满了青
苔杂草，旁边一根井绳。打水的桶也不知哪去了，看来很久没人用过
了。向井下望去，仿佛是个巢穴。

LONG);
	
	setup();
}
