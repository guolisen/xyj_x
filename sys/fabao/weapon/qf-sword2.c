// by firefox 03/21/2009

#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
	set_name("��潣", ({ "qingfeng sword", "sword" }) );
	set_weight(640);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "steel");
		set("long", "����۽���ɫ�̵��࣬�鶯������\n");
		//set("wield_msg", "$N���$n�������У����Ʒ�����졣\n");
		//set("unwield_msg", "$N��$n���뽣�ʣ��⻪���ա�\n");
	}
	init_dagger(20);
	setup();
}
