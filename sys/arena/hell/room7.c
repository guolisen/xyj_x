// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set("short", "�ε۵�");
	set("long", @LONG

�����������ظ�ʮ��֮�ε����Ĺ��ƽʱ�������£��ε�
������ڵ��ϴ���һЩ����

LONG);

	set("exits", (["east" : __DIR__"walk4"]));
	set("hell", 1);
	set("out_doors", 1);
	set("objects", ([
		"/d/death/npc/songdiwang" : 1,
		"/d/death/npc/tong" : 1,
	]));

	setup();
}
