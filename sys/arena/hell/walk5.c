// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set("short", "��˾");
	set("long", @LONG

����������ܵظ�֮�У�ż������������������˾��ǣ��Щ����
��������������ȥ��

LONG);

	set("exits", ([
		"south" : __DIR__"walk4",
		"west" : __DIR__"room9",
		"north" : __DIR__"walk6",
	]));
	set("hell", 1);

	setup();
}
