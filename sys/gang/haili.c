
#include <ansi.h>

inherit __DIR__"_base";

void create()
{
	_props = ([
		"id"		: "haili",
		"name"		: "����",
		"color"		: HIC,
		"from"		: "�ൺվ",
		"location"	: "����֮��",
		"slogan"	: "��ơ�ƣ��ϸ��ۣ�",
		
		"npc"		: ([
			"guard"		: ([
				"ids"		: ({"xian ge", "boy", "guard"}),
				"name"		: "С��",
				"family"	: "������",
				"weapon"	: "/d/obj/weapon/axe/bigaxe",				
				"props"		: ([ 
					"gender"	: "����",
					"long"		: "�ൺС�粻���ǣ�����î���ۣ�\n",
				]),
			]),
			"keeper"	: ([
				"ids"		: ({"lao bazi", "keeper"}),
				"name"		: "�ϰ���",
				"title"		: "�ܼ�",
				"props"		: ([
					"age"		: 60,
					"gender"	: "����",
					"long"		: "һλ�켣�ൺ������ϰ��ӣ�˿��������һ���ũ����Ϣ��\n",
				]),
			]),
			"npc1"		: ([
				"ids"		: ({"da man", "girl", "guard"}),
				"name"		: "��",
				"props"		: ([
					"age"		: 26,
					"per"		: 30,
					"gender"	: "Ů��",
					"long"		: "һλ�ӱ���10�ֵ���Ů��ûǮû��û������Զ�㡣\n",
				]),
			]),
			"npc2"		: ([
				"ids"		: ({"xiao man", "girl", "guard"}),
				"name"		: "С��",
				"props"		: ([
					"age"		: 16,
					"per"		: 30,
					"gender"	: "Ů��",
					"long"		: "�ȿ㡢Ĩ�أ�һ����һ��Ũ�صĺ�����ζ����һλ��׼��90���ൺС����\n"
				]),				
			]),
		]),

		"street"	: ([
			"short"		: "�¶�",
			"long"		: "\nɽ����ľ��ï�Դ䣬������һ������Ĵ󺣣�����һ��С·������\nͨ��һ��ɽկ��\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/changan/eastseashore",
			"verb"	: "down",
			"msg1"	: "$N����һ�е������������¡�",
			"msg2"	: "����һ���ҽУ�$N��ɽ���Ϲ�����������ͬһ̲����˦�ں�̲�ϡ�",
		]),

		"arrive"		: ([
			"dst"	: "/d/changan/eastseashore",
			"verb"	: "climb",
			"msg1"	: "$N������������ɽ������ȥ��",
			"msg2"	: "$N������������������ͷ��������ɽ��м��",
		]),
	]);

	setup();
}

