
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
		"id"		: "taishan",
		"name"		: "̩ɽ",
		"color"		: HIG,
		"from"		: "����վ",
		"location"	: "�����",
		"slogan"	: "�ᵱ�������һ����ɽС��",
		
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

	setup();
}
