// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit ROOM;

void create ()
{
	set ("short", "����");
	set ("long", @LONG

�����̲���Ʈ��һҶС�ۣ�һ��������Ů��ִ˫����������ˮ����������
����С�������������ǣ���������������̣���������������ַ��Ī��
ת��������������һЦ�����档��ɽ�������շ��������ʺ����ǹ��ꣿ��
����������а���������⡣

LONG);

	set("item_desc", ([
		"lotus" : "�ɻ��Ѿ�л�ˣ������Ϲ�����ĵ������\n",
	]));
	set("exits", ([
		"north" : __DIR__"rain",
	]));

	setup();
}

void init()
{
  add_action("do_dive", "dive");
}

int do_dive(string arg)
{
	if(cannot_move(_player)) return notify_fail("�����ڶ����ˡ�\n");

	message_vision(CYN"$N����һԾ����ͨһ�������������أ�\n"NOR, _player);
	_player->move(__DIR__"hudi");
	return 1;
}
