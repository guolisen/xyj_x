
#include <ansi.h>

inherit __DIR__"_base";

void create()
{
	_props = ([
		"id"		: "ftb",
		"name"		: "��ͷ��",
		"color"		: HIW,
		"location"	: "����������",
		"slogan"	: "ɽ������ǰ;��ְҵ��",
		
		"npc"		: ([
			"guard"		: ([
				"ids"		: ({"fu shou", "axer", "guard"}),
				"name"		: "����",
				"family"	: "������",
				"weapon"	: "/d/obj/weapon/axe/bigaxe",				
				"props"		: ([]),
			]),
			"keeper"	: ([
				"ids"		: ({"er dangjia", "keeper"}),
				"name"		: "������",
				"title"		: "������",
				"props"		: ([
					"age"		: 47,
					"long"		: "�����ҵ�ͷ������������������������˵���������꣬���������ġ�\n",
					"per"		: 5,
				]),
			]),
			"npc1"		: ([
				"ids"		: ({"xia zi", "blind man", "guard"}),
				"name"		: "Ϲ��",
				"props"		: ([
					"age"		: 37,
					"long"		: "�����۾��������ö��������������۾��������ª�����ˡ�\n",
					"per"		: 7,
				]),
			]),
			"npc2"		: ([
				"ids"		: ({"wang cai", "dog", "guard"}),
				"name"		: "����",
				"title"		: "��Ժ",
				"props"		: ([
					"race"		: "Ұ��",
					"age"		: 3,
					"long"		: "һֻ�ɰ���С����\n",
					"limbs"		: ({ "ͷ��", "����", "צ��", "����", "β��" }),
					"verbs"		: ({ "bite", "claw" }),
					"chat_chance"	: 2,
					"chat_msg"	: ({
						"�����ñ�����������Ľš�\n",
						"����ִ�ŵĿ���һ�����ӣ��·�����һ����ͷ��\n",
					}),
					"block_msg"	: "$N����ŵ�ס$n��ȥ·��\n",
				]),				
			]),
		]),

		"street"	: ([
			"short"		: "�¶�",
			"long"		: "\nɽ����ľ��ï�Դ䣬�����Ǽž������ɽ�ȣ�����һ��С·������\nͨ��һ��ɽկ��\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/westway/yinma",
			"verb"	: "down",
			"msg1"	: "$N����һ�е������������¡�",
			"msg2"	: "����һ���ҽУ�$N��ɽ���Ϲ�����������ͬһ̲����˦�ڵ��档",
		]),

		"arrive"		: ([
			"dst"	: "/d/westway/yinma",
			"verb"	: "climb",
			"msg1"	: "$N������������ɽ������ȥ��",
			"msg2"	: "$N������������������ͷ��������ɽ��м��",
		]),
	]);

	setup();
}

