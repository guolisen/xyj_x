// by firefox 02/21/2010

inherit ROOM;

#include <xyj_x.h>

void create ()
{
	set ("short", "����");
	set ("long", @LONG

�������ɨ�ĺܸɾ������ڴ����ð���������������˴������Ρ�

LONG);

	set("resource", ([ "water": 1 ]) );

	set("exits", ([
		"east" : __DIR__"backyard",
	]));

	set("objects", ([
		X_DIR"obj/food/tea"		: 1,
		"/d/lingtai/obj/baozi"	: 3,
	]));

	setup();
}
