// by firefox 03/21/2009

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
	set_name("��潣", ({ "qingfeng sword", "sword" }) );
	set_weight(780);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "steel");
		set("long", "����۽���ɫ�̵��࣬���س��ȡ�\n");
		//set("wield_msg", "$N���$n�������У��·�����������\n");
		//set("unwield_msg", "$N��$n���뽣�ʣ��⻪���ա�\n");
	}
	init_sword(70);
	setup();
}
