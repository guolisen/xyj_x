// by firefox 02/21/2010

inherit ROOM;
#include "_config.h"
#include "_stop_mx.h"

void create()
{
	set("short", "ɽկ��");
	set("long", "\n"
		"������һ���ܴ��ɽկ�����ǽ��¹���ܲ���կ�ų�����һ���\n"
		"��ӭ��Ʈ����鼸�����֣���" + GANG_NAME + "��\n\n"
	);
	set("exits", ([
		"south"		: __DIR__"street",
		"north"		: __DIR__"yard",
	]));

	set("objects", ([
		__DIR__"_guard" : 2,
	]));

	set("outdoors", 1);

	setup();
}

