
#include <ansi.h>

inherit __DIR__"_base";

void create()
{
	_props = ([
		"id"		: "dongxing",
		"name"		: "����",
		"color"		: HIM,
		"from"		: "-",
		"location"	: "����ɽ��",
		"slogan"	: "�����ڻ���Ĳ������",
		
		"npc"		: ([
			"guard"		: ([
				"ids"		: ({"xiao hunhun", "hunhun", "guard"}),
				"name"		: "С���",
				"family"	: "������",
				"weapon"	: "/d/gao/obj/blade",				
				"props"		: ([]),
			]),
			"keeper"	: ([
				"ids"		: ({"hei zai", "keeper"}),
				"name"		: "����",
				"title"		: "���޻�",
				"props"		: ([
					"per"		: 5,
				]),
			]),
			"npc1"		: ([
				"ids"		: ({"ya lang", "guard"}),
				"name"		: "����",
				"title"		: "���׻�",
				"props"		: ([
					"per"		: 7,
				]),
			]),
			"npc2"		: ([
				"ids"		: ({"dong weiping", "guard"}),
				"name"		: "��ΰƽ",
				"title"		: "��ɽ��",
				"props"		: ([
					"age"		: 30,
				]),				
			]),
		]),

		"street"	: ([
			"short"		: "�¶�",
			"long"		: "\nɽ����ľ��ï�Դ䣬�����Ǽž������ɽ�ȣ�����һ��С·������\nͨ��һ��ɽկ��\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/qujing/baoxiang/shanwan1",
			"verb"	: "down",
			"msg1"	: "$N����һ�е������������¡�",
			"msg2"	: "����һ���ҽУ�$N��ɽ���Ϲ�����������ͬһ̲����˦�ڵ��档",
		]),

		"arrive"		: ([
			"dst"	: "/d/qujing/baoxiang/shanwan1",
			"verb"	: "climb",
			"msg1"	: "$N�����ұڵķ�϶������������ɽ����ȥ��",
			"msg2"	: "$N������������������ͷ��������ɽ��м��",
		]),
	]);

	setup();
}

