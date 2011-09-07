// by firefox 11/21/2009

#include <ansi.h>
#include <xyj_x.h>

inherit ROOM;

void create ()
{
	dbase["short"]		= "山脚下";
	dbase["long"]		= "
前面一座高山，峰插碧空，真个是摩星碍日。暴雨刚过，新凉
透体，那真是：
" + "\n"HIG + "
    急雨收残暑，梧桐一叶惊。
    萤飞莎径晚，蛩语月华明。
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

