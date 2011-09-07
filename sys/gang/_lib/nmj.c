
#include "config.h"
inherit GROOT"base";

void create()
{
	prop_tab = ([
		"id"		: "nmj",
		"name"		: "������",
		"color"		: HIG,
		"location"	: "�Ϻ�������",
		"slogan"	: "������԰",
		
		"guard"		: ([
			"ids"		: ({"cai niao", "niao", "bird"}),
			"name"		: "����",
			"weapon"	: "/d/obj/weapon/rake/rake",
		]),

		"street"	: ([
			"short"		: "������",
			"long"		: "\n����һ�����ﻨ���ɽ�ȡ�������ˮ˳��ɽ�ȷ����к���������\n��ľ֦Ҷ�����ȸԾ������������Դ�ɾ�������������ѡ�\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/nanhai/zhulin8",
			"verb"	: "out",
			"msg1"	: "$N�ǿ�����������ȥ��",
			"msg2"	: "$N���Ǳ��Ĵ����������˳�����",
		]),

		"arrive"		: ([
			"dst"	: "/d/nanhai/zhulin8",
			"verb"	: "enter",
			"msg1"	: "$N�ǿ�����һͷ���˽�ȥ��",
			"msg2"	: "$N�����������˽�����",
		]),
	]);
}

