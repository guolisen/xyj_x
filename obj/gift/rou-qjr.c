// by firefox 11/12/2010

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"gift";

string eat_msg()
{
	_player->add("food", 20);				//����

	return "$N����$n���̻��ʵس�������ֱ�Ե��������͡�\n\n";
}


void create()
{
	set_name(RED"����"NOR, ({"zheng rou", "meat"}));

	set("unit","��");
	set("long","һ��ʷ����۵����⣬����ȡ������,Ҳ����ȡ�����ޣ�����ȡ���ˡ�\n");
	set("rewards", ([ DEXP : 20*K, PEXP : 20*K ]));
	set("eat_msg", (: eat_msg :));

	setup();
}

