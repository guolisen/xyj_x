// by firefox 11/21/2009

#include <weapon.h>
#include <ansi.h>

inherit SPEAR;

void create()
{
	set_name(HIR "���ǹ" NOR, ({ "huojianqiang", "spear" }));
	set_weight(10000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ��" HIR "���ǹ" NOR "�����Ǻ캢�����ҵı�����\n");
		set("material", "blacksteel");
		set("wield_msg","$N�����ǹ�������У���Χ���˶پ�һ���������������\n");
		set("unwield_msg", "$N�����е�$nϵ����������Ҳ��������ࡣ\n");
		set("weapon_prop/courage", 4);
		set("no_stock", 1);
	}
	init_spear(40);
	setup();
}

