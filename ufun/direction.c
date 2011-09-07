// by firefox 11/21/2009

mapping direction = ([
	"n"		: ({ "north",		"北",	"s",	({0, -1}) }),
	"e"		: ({ "east",		"东",	"w",	({1, 0}) }),
	"w"		: ({ "west",		"西",	"e",	({-1, 0}) }),
	"s"		: ({ "south",		"南",	"n",	({0, 1}) }),

	"nu"	: ({ "northup",		"北方",	"sd",	({0, -1}) }),
	"eu"	: ({ "eastup",		"东方",	"wd",	({1, 0}) }),
	"wu"	: ({ "westup",		"西方",	"ed",	({-1, 0}) }),
	"su"	: ({ "southup",		"南方",	"nd",	({0, 1}) }),

	"nd"	: ({ "northdown",	"北方",	"su",	({0, -1}) }),
	"ed"	: ({ "eastdown",	"东方",	"wu",	({1, 0}) }),
	"wd"	: ({ "westdown",	"西方",	"eu",	({-1, 0}) }),
	"sd"	: ({ "southdown",	"南方",	"nu",	({0, 1}) }),

	"ne"	: ({ "northeast",	"东北",	"sw",	({1, -1}) }),
	"nw"	: ({ "northwest",	"西北",	"se",	({-1, -1}) }),
	"se"	: ({ "southeast",	"东南",	"nw",	({1, 1}) }),
	"sw"	: ({ "southwest",	"西南",	"ne",	({-1, 1}) }),
]);

//英文方向
string en(string dir)
{
	return direction[dir][0];
}

//中文方向
string cn(string dir)
{
	return direction[dir][1];
}

//反方向
string opp(string dir)
{
	return direction[dir][2];
}

//方向的位移
int* offset(string dir)
{
	return direction[dir][3];
}
