// by firefox 02/21/2010

inherit ROOM;
#include <xyj_x.h>

void create ()
{
	set ("short", "����");
	set ("long", @LONG

ֻ��һ����������ǽ�Ƿ���һ¯̴�㣬һ˿�������޵�����������
�ơ�����������͸�����ʺ����ء�

LONG);

	set("exits", ([
		"east" : __DIR__"garden",
	]));

	set("objects", ([
		//GANG_DIR"_lib/danlu"	: 1,
	]));

	setup();
}
