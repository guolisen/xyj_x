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
		"east" : __DIR__"room8",
		"west" : __DIR__"room7",
		"north" : __DIR__"walk5",
	]));
	set("hell", 1);
	set("objects", (["/d/death/npc/gousiren" : 1]));

	setup();
}
