
#include "config.h"
inherit GROOT"base";

void create()
{
	prop_tab = ([
		"id"		: "ztb",
		"name"		: "��ͷ��",
		"color"		: HIM,
		"location"	: "�������",
		"slogan"	: "��ͷ��˧����ľ���",
		
		"guard"		: ([
			"ids"		: ({"lao muzhu", "muzhu", "zhu", "pig"}),
			"name"		: "��ĸ��",
			"weapon"	: "/d/obj/weapon/rake/rake",
		]),

		"street"	: ([
			"short"		: "�ص�",
			"long"		: "\n����һ��ֱͨ����Ϳ��⽼����ص���������ǳ��ڣ���Լ����\nС·������ͨ��һ��ɽկ��\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/kaifeng/shuaifu",
			"verb"	: "out",
			"msg1"	: "$N�ƶ����ţ�������ȥ��",
			"msg2"	: "ǽ�ǳ���һ�����ţ�$N���˳������漴����Ҳ��ʧ�ˡ�",
		]),

		"arrive"		: ([
			"dst"	: "/d/kaifeng/shuaifu",
			"verb"	: "enter",
			"msg1"	: "$N�������أ����һ�����ţ��漴����Ҳ��ʧ�ˡ�",
			"msg2"	: "$N�Ӱ��������˽�����",
		]),
	]);
}

