// by firefox 02/21/2010

#include <ansi.h>

inherit ROOM;
void create ()
{
	set ("short", "�᷿");
	set ("long", @LONG

����һ�����µĿͷ����ݽ���¯�ﴫ��һ�������㡣һ�ſ������
�Ĵ������ű��죬���˲��������˯��

LONG);

	set("exits", ([
		"west" : __DIR__"parlor",
	]));

	set("objects", ([
		__DIR__"_keeper" : 1,
	]));

	setup();
}
