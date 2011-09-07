inherit "/d/sldh2/guild/base";

#include "config.h"

void create()
{
	prop_tab = ([
		"id"            : "mllz",
		"name"          : "û������",
		"color"         : HIB,
		"location"      : "����������",
		"slogan"        : "����Ϊ�֣���������",

		"guard"         : ([
			"ids"           : ({"xiaoqing long", "long", "dragon"}),
			"name"          : "С����",
			"weapon"        : "/d/obj/weapon/axe/bigaxe",
		]),

		"street"        : ([
			"short"         : "������",
			"long"          : "\n�����ˮ���ƣ��������£���Ҷӯ֦����ȸ��������ˮ���ˣ���Ȫ\n���٣�����һ�������㳪������ӯҰ�ľ���\n\n",
		]),

		"leave"         : ([
			"dst"   : "/d/sea/maze0",
			"verb"  : "down",
			"msg1"  : "$N��ͨһ������ˮ��",
			"msg2"  : "$NͻȻ������ˮ�ס�",
		]),

		"arrive"                : ([
			"dst"   : "/d/sea/maze0",
			"verb"  : "swim",
			"msg1"  : "$N��ˮ����ȥ��",
			"msg2"  : "$N��ˮ��¶��ͷ����",
		]),
	]);
}
