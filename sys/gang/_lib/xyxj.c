inherit "/d/sldh2/guild/base";

#include "config.h"

void create()
{
	prop_tab = ([
		"id"            : "xyxj",
		"name"          : "��ң�ɽ�",
		"color"         : HIM,
		"location"      : "�����ɸ�",
		"slogan"        : "������Ϸ ��������",

		"guard"         : ([
			"ids"           : ({"xian tong", "tong", "guard"}),
			"name"          : "��ͯ",
			"weapon"        : "/d/obj/weapon/sword/qingfeng",
		]),

		"street"        : ([
			"short"         : "ʯ����",
			"long"          : "\n���к����������ȥ�ǰ������£��������Ȼ���ʣ�����һ������\n������������Դ��\n\n",
		]),

		"leave"         : ([
			"dst"   : "/d/penglai/road1",
			"verb"  : "out",
			"msg1"  : "$N�Ӷ�����һ��С��϶���˽�ȥ��",
			"msg2"  : "$N���±��ϵ�һ����϶�м��ѵļ��˳���",
		]),

		"arrive"                : ([
			"dst"   : "/d/penglai/road1",
			"verb"  : "enter",
			"msg1"  : "$N����±��ϵ�һ��С��϶��",
			"msg2"  : "$N���ѵļ�����ʯ����",
		]),
	]);
}
