
#include <ansi.h>

inherit __DIR__"_base";

void create()
{
	_props = ([
		"id"		: "huisuo",
		"name"		: "˽�˻���",
		"color"		: HIB,
		"from"		: "-",
		"location"	: "�����ַ�",
		"slogan"	: "�Ժ��ζ� �ӽ�������",
		
		"npc"		: ([
			"guard"		: ([
				"ids"		: ({"bao an", "guard"}),
				"name"		: "����",
				"family"	: "������",
				"weapon"	: "/d/obj/weapon/axe/bigaxe",				
				"props"		: ([ "gender" : "����" ]),
			]),
			"keeper"	: ([
				"ids"		: ({"wu shi", "keeper"}),
				"name"		: "����",
				"title"		: "�ܼ�",
				"props"		: ([
					"age"		: 50,
					"per"		: 5,
				]),
			]),
			"npc1"		: ([
				"ids"		: ({"yingbin xiaojie", "girl", "guard"}),
				"name"		: "ӭ��С��",
				"props"		: ([
					"age"		: 20,
					"per"		: 30,
					"gender"	: "Ů��",
					"block_msg"	: "$N��ס$n˵�����͹���ֹ����\n",
				]),
			]),
			"npc2"		: ([
				"ids"		: ({"anmo nvlang", "girl", "guard"}),
				"name"		: "��ĦŮ��",
				"props"		: ([
					"age"		: 18,
					"gender"	: "Ů��",

					"block_msg"	: "$N��ס$n˵�����͹���ֹ����\n",
				]),				
			]),
		]),

		"street"	: ([
			"short"		: "С��",
			"long"		: "\nС����߻谵������ͨ��һ��СԺ��\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/city/club",
			"verb"	: "out",
			"msg1"	: "$N�ƶ����ţ����˳�ȥ��",
			"msg2"	: "ǽ�ǳ���һ�����ţ�$N���˳������漴����Ҳ��ʧ�ˡ�",
		]),

		"arrive"		: ([
			"dst"	: "/d/city/club",
			"verb"	: "enter",
			"msg1"	: "$N�������أ����һ�����ţ��漴����Ҳ��ʧ�ˡ�",
			"msg2"	: "$N�Ӱ��������˽�����",
		]),
	]);

	setup();
}

