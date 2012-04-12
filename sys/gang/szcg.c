
#include <ansi.h>

inherit __DIR__"_base";

void create()
{
	mapping npc = ([
		"ids"		: ({"linshi gong", "guard"}),
		"name"		: "��ʱ��",
		"title"		: "С��ɱ��",
		"props"		: ([
			"age"			: 30,
			"chat_chance"	: 2,
			"chat_msg"		: ({
				"һ������һ�ѽ���һȺ��Ȯ�ǳǹܣ��������ĳ���ɫ�����ۺ������ΰ���\n",
				"ɱ��������ؤ�������ֻ�ɽ�����������غݣ�����ã��ҵ�̯λ�ٷ��\n",
			}),
			"block_msg"	: "$N��ס$n�������Ķ��ߣ��Ƚ�����!\n",
		]),	
	]);

	_props = ([
		"id"		: "szcg",
		"name"		: "���ݳǹ�",
		"color"		: HIR,
		"from"		: "����վ",
		"location"	: "����ɽ",
		"slogan"	: "���غݣ�����ã������ٷ��",
		
		"npc"		: ([
			"guard"		: ([
				"ids"		: ({"da shou", "guard"}),
				"name"		: "����",
				"title"		: "ִ��Ա",
				"family"	: "���޵ظ�",
				"weapon"	: "/d/qujing/qinglong/obj/stick",		
				"props"		: ([]),
			]),
			"keeper"	: ([
				"ids"		: ({"chumen jianxie", "keeper"}),
				"name"		: "���ż�Ѫ",
				"title"		: "���ӳ�",
				"props"		: ([
					"age"		: 47,
					"per"		: 5,
				]),
			]),
			"npc1"		: npc,
			"npc2"		: npc,
		]),

		"street"	: ([
			"short"		: "�¶�",
			"long"		: "\nɽ����ľ��ï�Դ䣬�����Ǽž������ɽ�ȣ�����һ��С·������\nͨ��һ��ɽկ��\n\n",
		]),

		"leave"		: ([
			"dst"	: "/d/death/huangwai",
			"verb"	: "down",
			"msg1"	: "$N����һ�е������������¡�",
			"msg2"	: "����һ���ҽУ�$N��ɽ���Ϲ�����������ͬһ̲����˦�ڵ��档",
		]),

		"arrive"		: ([
			"dst"	: "/d/death/huangwai",
			"verb"	: "climb",
			"msg1"	: "$N�����ұڵķ�϶������������ɽ������ȥ��",
			"msg2"	: "$N������������������ͷ��������ɽ��м��",
		]),
	]);

	setup();
}

