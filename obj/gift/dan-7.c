// by firefox 11/12/2010

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"gift";

//��ʮ������֮��
string eat_msg()
{
	_player->add_maximum_force(10);

	return "$N��$n�ӽ�����������ȥ���漴���һ��Ũ�̡�\n\n";
}


void create()
{
	set_name(RED"�߷���"NOR, ({"qifan huodan", "huodan" }));

	set("long", "�߷��������컯������֮ʿ���ô�һ�����ɵ���ʮ������֮����\n\n");
	set("rewards", ([ CEXP : 100*K ]));
	set("eat_msg", (: eat_msg :));

	setup();
}

