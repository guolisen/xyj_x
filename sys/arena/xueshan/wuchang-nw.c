// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set("short", "�����䳡");
	set("long", @LONG

���Ǳ���ǰ��һ��ƽ�أ�����ѩɽ��������֮�á����漫ƽ����
�����ˡ��������������С�ĵ㣬ѩɽ����Ҳ���ǽ�˶�������
���ȹ̹��򡣶����һ�����Ӷ���һ�ɴ���ȽȽ��������ǳ�
���ˡ�

LONG);

	set("exits", ([
		"south" : __DIR__"wuchang-w",
		"east" : __DIR__"wuchang-n",
	]));
	
	set("objects", ([
		"/d/obj/misc/ice" : 2,
	]));
	set("outdoors", "xueshan");

	setup();
}
