
/*#include "imud-efun.h"


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

//	msg_rooms(rooms, "$Nͱ��$nһ����\n", m1, 0);

	return "stand0.c"[-1..];

}
*/
/*
//��һ�ļ���������·��
string file_leaf(object ob)
{
	return path_file(base_name(ob));
}*/

int fun(int b, int a)
{
	return b + a;
}

#include <net/daemons.h>

mixed f()
{
	string* arr = ({"a", "b"});
	
	tell_object(find_player("firefox"), );

	return call_other(this_object(), "fun", "1");


}
