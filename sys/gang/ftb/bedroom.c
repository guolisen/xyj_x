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

	set("if_bed", 1);
	set("sleep_room", 1);

	set("no_fight", 1);
	set("no_magic", 1);
	
	set("valid_startroom", 1);
	set("no_upgrade_age", 1);

	set("exits", ([
		"east" : __DIR__"parlor",
	]));
	
	setup();

	call_other(__DIR__"board", "???");
}
