// by firefox 11/21/2009

#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
	set_name(HIC"��֮ս��"NOR, ({ "zhuzhi zhanjia" }));
	set_weight(1);
	if( clonep() )
		set_default_object(__FILE__);
	else {		
		set("long", "һ����͵Ļ��ף���˵�����������������˳ɳ���\n");
		set("material", "cloth");
		set("unit", "��");
		set("armor_prop/armor", 20);
		set("no_stock", 1);
	}
	setup();
}
