// by firefox 02/21/2010

inherit ROOM;

void create()
{
	set ("short", "����");
	set ("long", @LONG
		
������һ��С�ң�Ϊ�������ж������ṩ��һ���������ط���ǽ
�Ϲ���һ��������д�š�Ǳ˼�붨���ĸ��Ĵ��֡�

LONG);

	set("exits", ([
		"west": __DIR__"yard" 
	]));

	setup();

}
