// by firefox 02/21/2010

inherit ROOM;

void create()
{
	set("short", "�̳�");
	set("long", @LONG

���䳱ʪ��ɽ�����Ĵ��ɼ���ʯ���飬�鲼��������ͻ��һ����
ɭ�������Ϣ���м�һ��ǳǳ��ˮ�أ���ˮ�������������ԡ�

LONG
		);
	set("resource", ([ "water" : 1 ]));
	set("exits", ([
		"south"		: __DIR__"cave5",
		"north"		: __DIR__"xiaroom",
		"west"		: __DIR__"cave-w",
		"east"		: __DIR__"cave-e",
	]));

	setup();
}

