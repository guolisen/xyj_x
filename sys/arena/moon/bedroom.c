// by firefox 11/21/2009

#include <ansi.h>
inherit ROOM;

void create ()
{
	set ("short", "�Է�");
	set ("long", @LONG

һ�䵭����ɫ�ķ���, ���������, ��������������Ӱ˵��飬�Ժ���һ
�濪��һ����, ��ǰ����һ�������٣�ǽ����һ������ɫ����齡�

LONG);
	
	set("exits", ([
		"down" : __DIR__"rain",
	]));

	setup();
}
