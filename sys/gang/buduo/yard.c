// by firefox 02/21/2010

inherit ROOM;

void create ()
{
	set ("short", "��Ժ");
	set ("long", @LONG

����������涣��м�����ĳ�����������ϸϸ�Ļ������ʺ����䡣

LONG);

	set("outdoors", 1);
	set("exits", ([
		"south" : __DIR__"gate",
		"north" : __DIR__"parlor",
		"east" : __DIR__"study",
		"west" : __DIR__"practice",
	]));

	setup();
}
