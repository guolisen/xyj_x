// by firefox 11/12/2010

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"gift";

//���Ứ��ҩ�з������ȡ���ʹ֮Ч
string eat_msg()
{
	_player->add("water", -100);				//����
	_player->receive_curing("kee", 1000);	//��ʹ
	_player->receive_heal("kee", 1000);

	return "$N��$n�����������������ȥ��ֻ�е���̨���ޱȵ��徻�泩��\n\n";
}


void create()
{
	set_name(HIC"���Ứ"NOR, ({"puti flower", "puti", "flower"}));

	set("unit","��");
	set("long","���Ứ����������ҶҸ���Ѽ�����Ŀ������ͷ����ɶ�Ҹ����\n");
	set("rewards", ([ DEXP : 20*K, PEXP : 20*K ]));
	set("eat_msg", (: eat_msg :));

	setup();
}

