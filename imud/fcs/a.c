
#include "imud-efun.h"


mixed test()
{
	mapping m1 = ([
		"mid"	: "cn-xyj",
		"id"	: "laipi",
		"name"	: "��Ƥ",
	]);
	mapping m2 = ([
		"mid"	: "cn-xyj",
		"id"	: "firefox",
		"name"	: "���",
	]);
	object* rooms = ({ 
		load_object(__DIR__"0"),
		load_object(__DIR__"stand0"),
	});

	msg_rooms(rooms, "$Nͱ��$nһ����\n", m1, 0);

	return "stand0.c"[-1..];

}


int t()
{
	return intp(10);
}
