
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG

todo:��Ҫ������Ϣ��

LONG );

	set("exits", ([
		"south"   : __DIR__"lingxiao",
		"north"   : __DIR__"lingxiao",
		"west"   : __DIR__"lingxiao",
		"east"   : __DIR__"lingxiao",
	]));


	set("objects", ([
		__DIR__"anuo"   : 1,
		__DIR__"jiaye"   : 1,
		__DIR__"rulai"   : 1,
	]));

	setup();
}

void init()
{	
	//add_action("do_sa",  "sa");
}

int valid_leave(object me, string dir)
{
	return notify_fail("����������Ҷ���ߵ�ס��ȥ·��\n");
}
