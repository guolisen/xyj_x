// by firefox 11/21/2009

inherit "/d/sldh2/feature/whistle";

#include <ansi.h>

mixed* tab = ({
	({ HIR"ǧ��һյ��",	"һƥͨ������Ŀ���" }),
	({ HIC"������߾�",	"һƥ����ߵ�Ŀ���" }),
	({ HIB"û�������",	"һƥ������Ŀ���" }),
	({ HIW"̤�ڰ�ѩ��",	"һƥͨ��ѩ�׵Ŀ���" }),
	({ HIY"����",		"һƥ��¶���Ŀ���" }),
	({ HIR"��̿������",	"һƥͨ����Ŀ���" }),
	({ HIY"����͸����", "һƥ���½ý���ս��ͨ��Ȼƣ�ë����ɫ��" }),
});


void create()
{
	string* msg = random_1(tab);

	::create();

	ctor("/d/sldh2/feature/horse", ([
		"name"		: msg[0] + NOR,
		"long"		: msg[1],
		"come"		: "һ����˻��$n�ӹ����̳��м��۶�����",
		"leave"		: "һ����˻��$N������ȥ��",
	]));
}
