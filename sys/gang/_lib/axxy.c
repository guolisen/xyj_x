inherit "/d/sldh2/guild/base";

#include "config.h"

void create()
{
	prop_tab = ([
		"id"            : "axxy",
		"name"          : "��������",
		"color"         : HIR,
		"location"      : "����ɽ",
		"slogan"        : "�����������ڰ�",

		"guard"         : ([
			"ids"           : ({"kanmen ren", "ren", "guard"}),
			"name"          : "������",
			"weapon"        : "/d/obj/weapon/axe/bigaxe",
		]),

		"street"        : ([
			"short"         : "�¶�",
			"long"          : "\nɽ����ľ��ï�Դ䣬�����Ǽž������ɽ�ȣ�����һ��С·������\nͨ��һ��ɽկ��\n\n",
		]),

		"leave"         : ([
			"dst"   : "/d/changan/zhongnan",
			"verb"  : "down",
			"msg1"  : "$N����һ�е������������¡�",
			"msg2"  : "����һ���ҽУ�$N��ɽ���Ϲ�����������ͬһ̲����˦�ڵ��档",
		]),

		"arrive"                : ([
			"dst"   : "/d/changan/zhongnan",
			"verb"  : "climb",
			"msg1"  : "$N������������ɽ������ȥ��",
			"msg2"  : "$N������������������ͷ��������ɽ��м��",
		]),
	]);
}
