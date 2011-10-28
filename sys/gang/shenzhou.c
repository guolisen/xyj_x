
#include <ansi.h>

inherit __DIR__"_base";

mapping _guard = ([
	"ids"		: ({"shi wei", "wei", "guard"}),
	"name"		: "����",
	"family"	: "��ѩɽ",
	"weapon"	: "/d/obj/weapon/blade/handudao-blue",
	"props"		: ([]),
]);

void create()
{
	_props = ([
		"id"		: "shenzhou",
		"name"		: "����",
		"color"		: HIR,
		"from"		: "����վ",
		"location"	: "������",
		"slogan"	: "���ݴ�أ������졣",
		
		"npc"		: ([
			"guard"		: _guard,
			"keeper"	: ([
				"ids"		: ({"guan jia", "keeper"}),
				"name"		: "�ܼ�",
				"title"		: "�����ܹ�",
				"props"		: ([
					"age"		: 47,
					"long"		: "һλ�������Ϲܼҡ�\n",
				]),
			]),
			"npc1"		: _guard,
			"npc2"		: _guard,
		]),
		
		"street"	: ([
			"short"		: "�ص�",
			"long"		: "\n����һ��ֱͨ�����úͳ���������ص���������ǳ��ڣ���Լ����\nС·������ͨ��һ��ɽկ��\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/city/sanhua-mishi",
			"verb"	: "out",
			"msg1"	: "$N�ƶ����ţ�������ȥ��",
			"msg2"	: "ǽ�ǳ���һ�����ţ�$N���˳������漴����Ҳ��ʧ�ˡ�",
		]),

		"arrive"		: ([
			"dst"	: "/d/city/sanhua-mishi",
			"verb"	: "enter",
			"msg1"	: "$N�������أ����һ�����ţ��漴����Ҳ��ʧ�ˡ�",
			"msg2"	: "$N�Ӱ��������˽�����",
		]),
	]);

	setup();
}
