
#include "imud-efun.h"


mixed test()
{
	mapping m1 = ([
		"mid"	: "cn-xyj",
		"id"	: "laipi",
		"name"	: "ÀµÆ¤",
	]);
	mapping m2 = ([
		"mid"	: "cn-xyj",
		"id"	: "firefox",
		"name"	: "»ðºü",
	]);
	object* rooms = ({ 
		load_object(__DIR__"0"),
		load_object(__DIR__"stand0"),
	});

	msg_rooms(rooms, "$NÍ±ÁË$nÒ»µ¶¡£\n", m1, 0);

	return "stand0.c"[-1..];

}


int t()
{
	return intp(10);
}
