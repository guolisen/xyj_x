// by firefox 02/21/2010

inherit ROOM;

#include <ansi.h>

void create()
{
	set("short", "�׹Ƕ�");
	set("long", "\n\n"
"���䳱ʪ��ɽ�����Ĵ��ɼ���ʯ���飬�鲼��������ͻ��һ����\n"
"ɭ�������Ϣ���ı���"HIB BLINK"�׹�"NOR"��㣬��������\n\n"
	);
	set("exits", ([
		"south"		: __DIR__"cave3",
	]));

	set("objects", ([ __DIR__"npc/bai" : 1 ]) );

	setup();
}

