//Cracked by Roath

#include <ansi.h>
#include <dbase.h>
#include <armor.h>

inherit NECK;

void create()
{
        set_name(YEL"凋谢的黄菊花"NOR, ({ "yellow juhua", "juhua" }) );
        set("long", "\n一朵淡黄色的菊花!\n");
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("material", "steel");          
                set("no_sell", 1);
  							set("no_give", 1);
                set("no_drop", 1);
                set("no_put", 1);
                set("wear_msg", "$N拿出一朵淡黄色的$n戴在胸前。\n"NOR);
                set("value", 0);
                set("replace_file", "/obj/toy/fakebi");
								set("armor_prop/karma", 0);
        }
        setup();
}


        
