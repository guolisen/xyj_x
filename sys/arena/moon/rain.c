// by firefox 11/21/2009

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
	set ("short", "����¥");
	set ("long", @LONG

һ������ı���ɫС��¥, ���滷ˮ, ����һ����ˮ���ر߻���ӳˮ����
��������ϼ�������㣬�кɵ�㡣һ��ƽ̨��ˮ��������ʯΪ��������Ϊ
ש��̨�澧Ө��͸��ƽ���羵�������к��������

LONG);

	set("exits", ([
		"east"		: __DIR__"road3",
		"south"		: __DIR__"lotuspond",
		"up"		: __DIR__"bedroom",
	]));
	
	setup();
}
