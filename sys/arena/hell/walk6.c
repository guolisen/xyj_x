// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set("short", "��˾");
	set("long", @LONG

����һ�����������ȣ�û��ʲô���߶�����ΧҲû��ʲô������һ��
���Ǿ����ĵġ�������һ������שʯ�Ĺ������һ������֮�С�

LONG);

	set("exits", ([
		"south" : __DIR__"walk5",
		"northup" : __DIR__"cuiyun",
	]));
	set("hell", 1);

	set("objects", ([
		"/d/death/npc/tong2" : 1,
		"/d/death/npc/tong1" : 1,
	]));

	setup();
}

