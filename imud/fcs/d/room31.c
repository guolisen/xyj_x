
inherit ROOM;

void create()
{
	set ("short", "�߼�");
	set ("long", @LONG

һȺ��Χ����̴ľ������������ϯ����һλ���ݵ�ǩ�ͣ�����һ��
�����ش����ں���������һ��һ��������Ǭ��ǩ�����������ϡ�

LONG);

	set("exits", ([
		"west"		: __DIR__"room30"
	]));

	setup();
}
