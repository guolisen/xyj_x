
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
			"short"		: HIW"���¶�"NOR,
			"long"		: "\n�ڰ�ѩ�������¶���Ȼ��һ˿ů�磬�����ѩ�Ѿ��������ڣ�һ��\nС·����ͨ��һ��ɽկ��\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/xueshan/wroad11",
			"verb"	: "down",
			"msg1"	: "$N����һ������ͬ��ʯ����±��¡�",
			"msg2"	: "����һ���ҽУ�$N���¶��Ϲ�����������ѩ�����ҳ�һ���ӡ�",
		]),

		"arrive"		: ([
			"dst"	: "/d/xueshan/wroad11",
			"verb"	: "climb",
			"msg1"	: "$N���ű�϶��սս�������������ȥ��",
			"msg2"	: "$N�ӱ���������������һ��˪ѩ��",
		]),
	]);

	setup();
}
