// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set("short", "���䳡");
	set("long", @LONG

���Ǳ���ǰ��һ��ƽ�أ�����ѩɽ��������֮�á����漫ƽ����
�����ˡ��������������С�ĵ㣬ѩɽ����Ҳ���ǽ�˶�������
���ȹ̹���

LONG);

	set("exits", ([
		"south" : __DIR__"wuchang-sw",
		"north" : __DIR__"wuchang-nw",
		"east" : __DIR__"wuchang-c",
	]));
	
	set("objects", ([
		"/d/xueshan/npc/huangque-shier" : 1,
	]));

	set("outdoors", "xueshan");

	setup();
}
