// by firefox 02/21/2010

inherit ROOM;


void create()
{
	set("short", "����");
	set("long", @LONG

һ���ƹ������������ɽ���������������ɽ���ĳ��ڣ�һ���
��ʯ�����ſڡ�

LONG
		);
	set("no_fixup", 1);
	set("exits", ([
		"east"		: __DIR__"cave1",
	]));

	setup();
}

void init() 
{
	add_action("do_say", "say");

}

int do_say(string arg)
{
	object outer = load_object(__DIR__"yard");
	return outer->talk_to_door(this_player(), arg);
}

/*

����˿����������������

                ��ϼ��
                  ��
           �ܶ������̳ة����ܶ������ض�
                  ��
������    �׹Ƕ� ���� �һ���
��   ������ ��    ��    �� 
     ʯ�ҩ������ک������Щ�������
                  ��
                 ����
                  ��
     ��ǰ�������ک�������


*/
