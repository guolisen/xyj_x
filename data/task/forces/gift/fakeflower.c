//Cracked by Roath

#include <ansi.h>
#include <dbase.h>
#include <armor.h>

inherit NECK;

void create()
{
        set_name(YEL"��л�Ļƾջ�"NOR, ({ "yellow juhua", "juhua" }) );
        set("long", "\nһ�䵭��ɫ�ľջ�!\n");
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("material", "steel");          
                set("no_sell", 1);
  							set("no_give", 1);
                set("no_drop", 1);
                set("no_put", 1);
                set("wear_msg", "$N�ó�һ�䵭��ɫ��$n������ǰ��\n"NOR);
                set("value", 0);
                set("replace_file", "/obj/toy/fakebi");
								set("armor_prop/karma", 0);
        }
        setup();
}


        
