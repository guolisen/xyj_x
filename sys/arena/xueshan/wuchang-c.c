// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set ("short", "�����䳡");
	set ("long", @LONG

���Ǳ���ǰ��һ��ƽ�أ�����ѩɽ��������֮�á����漫ƽ����
�����ˡ��������������С�ĵ㣬ѩɽ����Ҳ���ǽ�˶�������
���ȹ̹���

LONG);

	set("exits", ([
		"south" : __DIR__"wuchang-s",
		"north" : __DIR__"wuchang-n",
		"west" : __DIR__"wuchang-w",
		"east" : __DIR__"wuchang-e",
	]));
	
	set("objects", ([
		"/d/xueshan/npc/xunshi" : 2,
		"/d/xueshan/npc/yingwu-guai" : 1,
		"/d/obj/misc/ice.c" : 1,
	]));

	set("outdoors", "xueshan");

	setup();
}

