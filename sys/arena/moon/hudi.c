// by firefox 11/21/2009

#include <ansi.h>

inherit ROOM;

void create ()
{
	set ("short", "����");
	set ("long", @LONG

���˺���������ף������������Ⱦ�����������壮
LONG);
	set("exits", ([
		"up" : __DIR__"lotuspond",
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	message_vision(CYN"$Nƴ�����������ϰ��������������ˮ��\n"NOR, me);
	me->set("water", (int)me->max_water_capacity());
	return ::valid_leave(me, dir);
}
