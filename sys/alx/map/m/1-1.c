// by firefox 11/21/2009

#include <ansi.h>
#include <xyj_x.h>

inherit ROOM;

void create ()
{
	dbase["short"]		= "ɽ����";
	dbase["long"]		= "
ǰ��һ����ɽ�����̿գ������Ħ�ǰ��ա�����չ�������
͸�壬�����ǣ�
" + "\n"HIG + "
    �����ղ����ͩһҶ����
    ө��ɯ���������»�����
" + "\n"NOR;

	dbase["exits"]		= ([
		"south"		: this_object(),
		"north"		: "/d/city/qingxuguan",
		"west"		: this_object(),
		"east"		: this_object(),
	]);
		
	dbase["objects"]	= ([ __DIR__"panguan" : 1 ]);
	
	setup();
}

