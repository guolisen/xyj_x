
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
	mixed c = 1;
	mixed d;

	if(undefinedp(c)) write("undefinedp(c)\n");
	if(undefinedp(d)) write("undefinedp(d)\n");

	return b + a;
}

#include <net/daemons.h>

mixed f()
{

	mixed* arr1 = allocate(10);

	string* arr = ({"a", "b"});

	if(sscanf("1:2:3:a:b", "%d:%d:%d:%s:%s", arr1[0], arr1[1], arr1[2], arr1[3], arr1[4])) {
		printf("%d:%d:%d:%s:%s\n", arr1[0], arr1[1], arr1[2], arr1[3], arr1[4]);
	}
	
	tell_object(find_player("firefox"), );

	return explode("", ":");


}
