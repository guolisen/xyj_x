// by firefox 02/21/2010

inherit ROOM;

#include <ansi.h>

void create()
{
	set("short", "�һ���");
	set("long", "\n\n"
"���䳱ʪ��ɽ�����Ĵ��ɼ���ʯ���飬�鲼��������ͻ��һ����\n"
"ɭ�������Ϣ��ǽ��б�弸֦"HIM"�һ�"NOR"�����ܹ���֩������\n\n"
	);

	set("exits", ([
		"south"		: __DIR__"cave4",
	]));

	set("objects", ([ __DIR__"npc/chun" : 1 ]) );

	setup();
}

