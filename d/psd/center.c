// by firefox 02/21/2010

inherit ROOM;


void create()
{
	set("short", "����");
	set("long", @LONG

���䳱ʪ��ɽ�����Ĵ��ɼ���ʯ���飬�鲼��������ͻ��һ����
ɭ�������Ϣ�����･��������������ʮ�ˡ�

LONG
		);

	set("exits", ([
		"south"		: __DIR__"cave2",
		"west"		: __DIR__"cave3",
		"east"		: __DIR__"cave4",
		"north"		: __DIR__"cave5",
	]));

	setup();
}
