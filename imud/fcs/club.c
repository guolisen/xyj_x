
inherit ROOM;

void create ()
{
	set ("short", "�����ַ�");
	set ("long", @LONG

�����ǳ�����һ�����������ֳ�������ҹĻ���ٺ�����͸������֡�
���������Ŀ����д�ٹ��ˣ��������������ã��˼����ĵ����ӣ���
���Ⱥ�ı�ʿ����ʱҲ�ܿ���һЩ���׿ʹ���ɮ�˻��ʿ��

LONG);

	set("exits", ([
		"up"		: __DIR__"club2",
		"east"		: __DIR__"zhuque-s2",
	]));

	set("objects", ([
		__DIR__"npc-boss" : 1,
	]));

	setup();

}

