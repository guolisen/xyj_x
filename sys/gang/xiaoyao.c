
#include <ansi.h>

inherit __DIR__"_base";

void create()
{
	_props = ([
		"id"		: "xiaoyao",
		"name"		: "��ң��",
		"color"		: HIM,
		"from"		: "-",
		"location"	: "�ٻ���",
		"slogan"	: "�ٻ����� ��ң���ڣ�",
		
		"npc"		: ([
			"guard"		: ([
				"ids"		: ({"xian tong", "tong", "guard"}),
				"name"		: "��ͯ",
				"family"	: "������",
				"weapon"	: "/d/obj/weapon/axe/bigaxe",				
				"props"		: ([ "gender" : "����" ]),
			]),
			"keeper"	: ([
				"ids"		: ({"tiao tiao", "keeper"}),
				"name"		: "����",
				"title"		: "������",
				"props"		: ([
					"age"		: 10,
					"per"		: 5,
				]),
			]),
			"npc1"		: ([
				"ids"		: ({"xian zi", "girl", "guard"}),
				"name"		: "����",
				"props"		: ([
					"age"		: 20,
					"per"		: 30,
					"gender"	: "Ů��",
				]),
			]),
			"npc2"		: ([
				"ids"		: ({"xian he", "he", "guard"}),
				"name"		: "�ɺ�",
				"props"		: ([
					"race"		: "Ұ��",
					"age"		: 3,
					"limbs"		: ({ "ͷ��", "����", "צ��", "����", "β��" }),
					"verbs"		: ({ "bite", "claw" }),

					"block_msg"	: "$Nչ�ᵲס$n��ȥ·��\n",
				]),				
			]),
		]),

		"street"	: ([
			"short"		: "�¶�",
			"long"		: "\nɽ����ľ��ï�Դ䣬�����Ǽž������ɽ�ȣ�����һ��С·������\nͨ��һ��ɽկ��\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/penglai/baihuagu1",
			"verb"	: "down",
			"msg1"	: "$N����һ�е������������¡�",
			"msg2"	: "����һ���ҽУ�$N��ɽ���Ϲ�����������ͬһ̲����˦�ڵ��档",
		]),

		"arrive"		: ([
			"dst"	: "/d/penglai/baihuagu1",
			"verb"	: "climb",
			"msg1"	: "$N�����ұڵķ�϶������������ɽ������ȥ��",
			"msg2"	: "$N������������������ͷ��������ɽ��м��",
		]),
	]);

	setup();
}

