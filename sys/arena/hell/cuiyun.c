// by firefox 11/21/2009

inherit ROOM;

void create()
{
	set("short", "���ƹ�");
	set("long", @LONG

��������������ܵظ������¹��ĵز����������й������ϲ�û��
ʲô�����װ�Σ���ֵ������Ҹ����˰˸���ɫ��ʯ����ÿ�����а�
���Ű���ô������һ�����������ϰ����ľߣ�һ������СͲ��װ��
���������

LONG);

	set("exits", ([ "southdown" : __DIR__"walk6"]));
	set("hell", 1);
	set("out_doors", 1);
	set("objects", (["/d/death/npc/dizhang" : 1]));

	setup();
}
