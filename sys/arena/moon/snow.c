// by firefox 11/21/2009

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create ()
{
	set ("short", "�߷���");
	set ("long", @LONG

�˴��������䣬ȴ�����˱ǡ�һ�껨ľҲ�ޣ�ֻ�������ݣ�����ǣ�ٵ�
�����������ģ���ɽ�ۣ���ʯ϶���������������������̽ס���Щ��
�����٣��������Դ䣬������ʵ����ɺ������һ�㣬�۴��ɰ���������ѩ
��һ�㣬һɫ������ȫ�ޡ�����ֻ��һ������ƿ��ƿ�й�����֦�ա�

LONG);

	set("objects", ([
		"/d/obj/flower/juhua.c" : 1,
	]));
	set("exits", ([ /* sizeof() == 1 */
		"west" : __DIR__"road3",
	]));

	setup();
}
