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
        
    tell_object(me, name()+"������ʼ��л�ˡ�\n");
    message_vision("$N���ϵ�$n�����ĵ�л�ˡ�\n",me,this_object());
    fake = new ("//d/obj/gift/fakeflower");
    fake -> move(me);  
    destruct(this_object());
    
}

void create()
{
        set_name(YEL"�ƾջ�"NOR, ({ "yellow juhua", "juhua" }) );
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
    				    set("no_get", 1);
                set("no_put", 1);
                set("wear_msg", "$N�ó�һ�䵭��ɫ��$n������ǰ��\n"NOR);
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
        message_vision(HIB"ֻ��һ����������...$N��ʬ����ʲô������ʧ�ˡ�\n"NOR,me);
        destruct(this_object());
        return;
}
void destruct_me(object where, object me)
{
        message_vision("$N�����$n�����Ŀ�ή�ˣ��������Ʈɢ��ȥ��\n",where,me);
        destruct(me);
}

