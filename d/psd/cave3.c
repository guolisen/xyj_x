// by firefox 02/21/2010

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG

���䳱ʪ��ɽ�����Ĵ��ɼ���ʯ���飬�鲼��������ͻ��һ����
ɭ�������Ϣ��

LONG
		);

	set("exits", ([
		"west"		: __DIR__"bedroom",
		"east"		: __DIR__"center",
		"north"		: __DIR__"bairoom",
	]));

	setup();
}

