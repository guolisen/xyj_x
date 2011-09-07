// by firefox 02/21/2010

inherit ROOM;

#include <room.h>
#include "_config.h"
#include <ansi.h>

#define ARROW		"/d/obj/weapon/archery/zhujian"

void create ()
{
	set ("short", "�԰");
	set ("long", @LONG

һƬ������԰�֣����ǹ�����Ϣ�ļѴ����м�һ��Сˮ�������
�����������㡣ǽ��һ��ʫ��

    ����б�����ǰ�����԰�Ǹ��ɳ�̨��
    �������´����̣����Ǿ�����Ӱ����

LONG);

	set("resource", ([ "water": 1 ]) );
	set("outdoors", 1);
	set("exits", ([
		"south" : __DIR__"backyard",
		"north" : __DIR__"backroom",
		"east" : __DIR__"animal",
		"west" : __DIR__"medicine",
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	if(dir == "north" && !G->is_executive(me)) {
		object arrows = new(ARROW);
		arrows->set_amount(3 + random(5));
		arrows->move(this_object());
		message_vision(HIW"$N������ȥ��ͻȻ�����Ҽ��뷢��$N���˶��������һ���亹��\n\n"NOR, me);
		if(!me->is_busy()) me->start_busy(20);
		me->command("sweat");
		return notify_fail("\n");
	}
	return ::valid_leave(me, dir);
}

