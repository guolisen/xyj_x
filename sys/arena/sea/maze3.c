// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set("short", "����ç��");
	set("long", @LONG

����ˮɫ��Ļ�����������Χ�ѿ���������ˡ�ż�а���Ϯ������
��������������Ĵ�����Щ�߸ߵĺ��ݣ����������ͷ���ڵ�һ˿
��âҲû���ˡ�

LONG);

	set("exits", ([
		"east" : __DIR__"maze1",
		"north" : __DIR__"maze2",
		"south" : __DIR__"maze4",
		"west" : __DIR__"maze5",
	]));

	set("water", 1);

	setup();
}

