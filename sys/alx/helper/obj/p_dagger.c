// by firefox 11/21/2009

#include <weapon.h>
#include <ansi.h>

inherit DAGGER;

void create()
{
	set_name(WHT"�����ħצ"NOR, ({"deathtouch" }) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ����ɫ�����С�\n");
		set("value", 55);
		set("material", "steel");
	}
	init_dagger(40);

	set("wield_msg", "$N�ӻ�������һ��$n�������С�\n");
	set("unwield_msg", "$N�����е�$n���뻳�С�\n");

	setup();
}
