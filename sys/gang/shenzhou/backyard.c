// by firefox 02/21/2010

inherit ROOM;

void create ()
{
	set ("short", "��Ժ");
	set ("long", @LONG

��Ժ�����������տյ�������Ҷ��أ�Ҳû���˴�ɨ������Ʈ��
һ�����㡣

LONG);

	set("outdoors", 1);
	set("exits", ([
		"south" : __DIR__"parlor",
		"north" : __DIR__"garden",
		"east" : __DIR__"z2",
		"west" : __DIR__"kitchen",
	]));

	setup();
}
