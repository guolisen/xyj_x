// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set ("short", "�ع��");
	set ("long", @LONG

�����������ظ�ʮ��֮�ع����Ĺ��ƽʱ�������£��ع�
������ڵ��ϴ���һЩ����

LONG);

	set("exits", (["east" : __DIR__"walk5"]));
	set("hell", 1);

	set("objects", ([
		"/d/death/npc/qinguangwang" : 1,
		"/d/death/npc/tong" : 1,
	]));

	setup();
}
