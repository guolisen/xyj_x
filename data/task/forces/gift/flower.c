//Cracked by Roath


#include <ansi.h>
#include <dbase.h>
#include <armor.h>

inherit NECK;

void init()
{ object me=this_player();	
  
  if(userp(this_player()))
      call_out("self_dest",21600,me);
}

void self_dest(object me)
{	string ctime;
	object fake;
        
    tell_object(me, name()+"渐渐开始凋谢了。\n");
    message_vision("$N身上的$n渐渐的凋谢了。\n",me,this_object());
    fake = new ("//d/obj/gift/fakeflower");
    fake -> move(me);  
    destruct(this_object());
    
}

void create()
{
        set_name(YEL"黄菊花"NOR, ({ "yellow juhua", "juhua" }) );
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
    				    set("no_get", 1);
                set("no_put", 1);
                set("wear_msg", "$N拿出一朵淡黄色的$n戴在胸前。\n"NOR);
                set("replace_file", "/d/obj/gift/fakeflower");
                set("value", 0);
//		set("armor_prop/karma", random(10));
		set("armor_prop/intelligence",10);
        }
        setup();
}
void owner_is_killed()
{
        object me = this_player();
        message_vision(HIB"只见一阵烟雾闪过...$N的尸体上什么东西消失了。\n"NOR,me);
        destruct(this_object());
        return;
}
void destruct_me(object where, object me)
{
        message_vision("$N手里的$n慢慢的枯萎了，随着清风飘散而去。\n",where,me);
        destruct(me);
}

