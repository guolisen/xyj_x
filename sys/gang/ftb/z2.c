// by firefox 02/21/2010

#include <ansi.h>

inherit ROOM;

void create ()
{
	set ("short", "��");
	set ("long", @LONG

����һ��񷿣���������˲�ݣ���֦������һЩ�������ҵ���
���Ĵ���

LONG);

	set("exits", ([
		"west" : __DIR__"backyard",
	]));


	setup();
}
