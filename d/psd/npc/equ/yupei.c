// by firefox 03/21/2009

#include <armor.h>
inherit NECK;

void create()
{
	set_name("����", ({"yu pei"}));
	set_weight(800);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 2000);
		set("long", "һö���壬����һ���֣�ӨӨ�����ǣ�ƣ�������˼�����С�\n");
		set("no_sell", 1);
		set("material", "steel");
		set("armor_prop/spells", 30);

	}
	setup();
}

