
#include <ansi.h>

inherit __DIR__"_base";

mapping _guard = ([
	"ids"		: ({"huo qilin", "qilin", "guard"}),
	"name"		: "������",
	"family"	: "���ƶ�",
	"weapon"	: "/d/obj/weapon/rake/rake",
	"props"		: ([]),
]);

void create()
{
	_props = ([
		"id"		: "buduo",
		"name"		: "�����ֻؽ�",
		"color"		: HIY,
		"location"	: "����ɽ",
		"slogan"	: "���ϵ��£�Ψ�Ҷ���",
		
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
			"short"		: "������",
			"long"		: "\n���ǻ���ɽ�ϵ�һ��Ͽ�ȣ�ʯ���϶�����Ѭ���ǵĺۼ�����������\nС·������ͨ��һ��ɽկ��\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/qujing/firemount/nofire",
			"verb"	: "up",
			"msg1"	: "$N�������ɽ����ȥ��",
			"msg2"	: "$N��������������������",
		]),

		"arrive"		: ([
			"dst"	: "/d/qujing/firemount/nofire",
			"verb"	: "jump",
			"msg1"	: "$N����һԾ������ɽ�ȡ�",
			"msg2"	: "һ�����죬$Nſ�ڵ���һ��������",
		]),
	]);

	setup();
}
