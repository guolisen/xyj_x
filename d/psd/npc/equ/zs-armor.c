// by firefox 03/21/2009

#include <armor.h>

inherit ARMOR;

void create()
{
        set_name("��˿���", ({"zhusi armor", "armor"}));
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
				set("long", "һ�������������ס�\n");
                set("material", "silk");
                set("value", 200);
                set("armor_prop/armor", 55);
        }
        setup();
}


