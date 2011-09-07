// by firefox 11/21/2009

#include <xyj_x.h>

inherit ROOM;

#include <ansi.h>

void create ()
{
	set ("short", HIW"������"NOR);
	set ("long", @LONG

��Լ�����ֳ�һ����ɫ��¥������̫������������������������
�޿�������ж�ǰ������Ϊһ�����Źؾ��޷��ٻ������ˡ���Χ��
�ߵ�Ұ�����ҡ�ڣ����з��������ķ�����
LONG);

	set("exits", ([
		"south"		: this_object(),
		"north"		: this_object(),
		"west"		: this_object(),
		"east"		: this_object(),])
	);
	
	set("no_fight", 1);
	set("no_magic",1);
	set("alternative_die", 1);
	
	set("objects", ([ __DIR__"panguan" : 1 ]));
	
	setup();
}

void init()
{
	if(!_player->is_busy()) _player->start_busy(2);
}

void alternative_die(object who)
{
	HP->full(who, 1);
}

int clean_up()
{
	return 0;
}
