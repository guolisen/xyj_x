// by firefox 02/21/2010

inherit ROOM;

#include <xyj_x.h>

void create()
{
	set("short", "ʯ��");
	set("long", @LONG

���䳱ʪ��ɽ�����Ĵ��ɼ���ʯ���飬�鲼��������ͻ��һ����
ɭ�������Ϣ��ǽ������һ�㵾�ݡ�

LONG
		);

	set("objects", ([
		"/d/ourhome/obj/jitui" : 4,
		X_DIR"obj/food/tea" : 2,
	]));
	set("resource", ([ "water" : 1 ]));
	set("valid_startroom", 1);
	set("sleep_room", 1);

	set("exits", ([
		"east"		: __DIR__"cave3",
	]));

	setup();
}
