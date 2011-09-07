// by firefox 11/21/2009

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
	set("short", HIW"雪山之巅"NOR);
	set("long", @LONG

这里是雪山的最高峰，万里晴空下是无尽的皑皑白雪，南面就是雪山的练
武场，雪山弟子的一举一动的都看得清清楚楚。

LONG);
	
	setup();
}
