// by firefox 02/21/2010

inherit ROOM;

#include "_config.h"
#include "_stop_mx.h"

void create ()
{
	set ("short", "����");
	set ("long", @LONG

�������䲼�õĹ��Ӵ󷽣����ſڹ���һ��������顺Ψ�Ҷ��𡻡�

LONG);

	set("exits", ([
		"south" : __DIR__"yard",
		"north" : __DIR__"backyard",
		"west" : __DIR__"bedroom",
		"east" : __DIR__"z1",
	]));

	set("objects", ([
		__DIR__"_npc1"			: 1,
		__DIR__"_npc2"			: 1,
	]));

	setup();
}
