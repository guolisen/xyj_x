// by firefox 02/21/2010

#include <ansi.h>

inherit ROOM;

void create ()
{
	set ("short", "����");
	set ("long", @LONG

����һ���̶��ҿ������������������ѱ����������Ұ�ޣ�һ
���Ǹ��õط���

LONG);

	set("exits", ([
		"west" : __DIR__"garden",
	]));

	setup();
}
