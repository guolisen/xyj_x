// by firefox 02/21/2010

inherit ROOM;


void create()
{
	set("short", "����");
	set("long", @LONG

���䳱ʪ��ɽ�����Ĵ��ɼ���ʯ���飬�鲼��������ͻ��һ����
ɭ�������Ϣ���ı��ϵ�ˮ�鲻�ϵ��䡣

LONG
		);

	set("exits", ([
		"west"		: __DIR__"pool",
		"east"		: __DIR__"backroom",
	]));

	setup();
}

