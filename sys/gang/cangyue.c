
#include <ansi.h>

inherit __DIR__"_base";

void create()
{
	_props = ([
		"id"		: "cangyue",
		"name"		: "����",
		"color"		: HIC,
		"from"		: "С������",
		"location"	: "������",
		"slogan"	: "��ң���ڣ������ڻ��",
		
		"npc"		: ([
			"guard"		: ([
				"ids"		: ({"yin shi", "guard"}),
				"name"		: "��ʿ",
				"title"		: "С�����˺�",
				"family"	: "���޵ظ�",
				"weapon"	: "/d/qujing/qinglong/obj/stick",		
				"props"		: ([]),
			]),
			"keeper"	: ([
				"ids"		: ({"xiaoyao shu", "keeper"}),
				"name"		: "��ң��",
				"title"		: "С��ܼ�",
				"props"		: ([
					"age"		: 47,
					"per"		: 5,
				]),
			]),			
			"npc1"		: ([
				"ids"		: ({"bai qi", "guard"}),
				"name"		: "��������",
				"title"		: "С��ɱ�˿�",
				"props"		: ([
				]),
			]),
			"npc2"		: ([
				"ids"		: ({"hua bianque", "guard"}),
				"name"		: "����ȵ",
				"title"		: "С������",
				"props"		: ([
				]),				
			]),
		]),

		"street"	: ([
			"short"		: "�¶�",
			"long"		: "\nɽ����ľ��ï�Դ䣬�����Ǽž������ɽ�ȣ�����һ��С·������\nͨ��һ��ɽկ��\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/southern/wutai/qinglianggu",
			"verb"	: "down",
			"msg1"	: "$N����һ�е������������¡�",
			"msg2"	: "����һ���ҽУ�$N��ɽ���Ϲ�����������ͬһ̲����˦�ڵ��档",
		]),

		"arrive"		: ([
			"dst"	: "/d/southern/wutai/qinglianggu",
			"verb"	: "climb",
			"msg1"	: "$N������������ɽ������ȥ��",
			"msg2"	: "$N������������������ͷ��������ɽ��м��",
		]),
	]);

	setup();
}

