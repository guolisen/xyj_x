// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG

�����������ظ�ʮ��֮�������Ĺ��ƽʱ�������£�����
������ڵ��ϴ���һЩ����

LONG);

	set("exits", (["west" : __DIR__"walk4"]));
	set("hell", 1);
	set("objects", ([
		"/d/death/npc/chujiangwang" : 1,
		"/d/death/npc/tong" : 1,
	]));

	setup();
}
