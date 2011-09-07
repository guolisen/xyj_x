// by firefox 11/21/2009

mapping direction = ([
	"n"		: ({ "north",		"��",	"s",	({0, -1}) }),
	"e"		: ({ "east",		"��",	"w",	({1, 0}) }),
	"w"		: ({ "west",		"��",	"e",	({-1, 0}) }),
	"s"		: ({ "south",		"��",	"n",	({0, 1}) }),

	"nu"	: ({ "northup",		"����",	"sd",	({0, -1}) }),
	"eu"	: ({ "eastup",		"����",	"wd",	({1, 0}) }),
	"wu"	: ({ "westup",		"����",	"ed",	({-1, 0}) }),
	"su"	: ({ "southup",		"�Ϸ�",	"nd",	({0, 1}) }),

	"nd"	: ({ "northdown",	"����",	"su",	({0, -1}) }),
	"ed"	: ({ "eastdown",	"����",	"wu",	({1, 0}) }),
	"wd"	: ({ "westdown",	"����",	"eu",	({-1, 0}) }),
	"sd"	: ({ "southdown",	"�Ϸ�",	"nu",	({0, 1}) }),

	"ne"	: ({ "northeast",	"����",	"sw",	({1, -1}) }),
	"nw"	: ({ "northwest",	"����",	"se",	({-1, -1}) }),
	"se"	: ({ "southeast",	"����",	"nw",	({1, 1}) }),
	"sw"	: ({ "southwest",	"����",	"ne",	({-1, 1}) }),
]);

//Ӣ�ķ���
string en(string dir)
{
	return direction[dir][0];
}

//���ķ���
string cn(string dir)
{
	return direction[dir][1];
}

//������
string opp(string dir)
{
	return direction[dir][2];
}

//�����λ��
int* offset(string dir)
{
	return direction[dir][3];
}
