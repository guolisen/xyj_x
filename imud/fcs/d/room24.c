
inherit ROOM;

void create()
{
	set ("short", "�߼�");
	set ("long", @LONG

һȺ��Χ����̴ľ������������ϯ����һλ���ݵ�ǩ�ͣ�����һ��
�����ش����ں���������һ��һ��������Ǭ��ǩ�����������ϡ�

LONG);

	set("exits", ([
		"south"		: __DIR__"room20"
	]));

	setup();
}
