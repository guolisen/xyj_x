//Cracked by Roath
#include <ansi.h>
#define LAST_PAR "sm"
#define THIS_PAR "smwl"
#define GIFT_NAME "���ռ���Ʒ"
inherit ITEM;
void create()
{
    set_name(WHT + GIFT_NAME + NOR, ({"gift","liwu"}));
    set_weight(20);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "��");
        set("long",
              HIR+"                ������������������������������������������������
                ��                                            �� 
                ��  "HIY"���μǱ�վ��ʦ�飺"HIR"                        �� 
                ��                                            �� 
                ��   "HIY"    �������Ȱ�MUD�Ȱ�XYJ������¾�"HIR"       �� 
                ��                                            �� 
                ��   "HIY"         ϣ�������ܹ�ά����վ!  "HIR"         �� 
                ��                                            �� 
                ��                                            �� 
                ��                       "HIW"       addoil!"HIR"       �� 
                ��                       "HIY"          ���С��"HIR"   �� 
                ������������������������������������������������
�����ൺվ��ʦ���һ��С���⣬���(chai)��������ʲô��
"NOR
);
    set("value", 0);
    set("no_give",1);
    set("no_get",1);
    set("no_put",1);
    set("no_drop",1);
  }
    setup();
}
void init()
{
    add_action("do_chai", "chai");
}
int do_chai(string arg)
{
     object me = this_player();
     int jp = me->query("combat_exp");
//     object ob = new("/obj/money/gold");
//     object item = new("/d/penglai/npc/obj/guai");
       object item1 = new("/d/obj/gift/flower");
//     object item2 = new("/d/lingtai/obj/faguan");


  if (!id(arg))  return notify_fail("��Ҫ��ʲô��\n");

  if (!me->query(THIS_PAR + "_smwl"))  {
   if(me->query("combat_exp") < 25000) return notify_fail("�����ѧ������25000�㡣\n"); 
 //      destruct(ob);
    //   item->move(me);
         item1->move(me);
   //    item2->move(me);
         me->add("potential",10000);
  //     me->add("max_force", 600);
  //     me->add("maximum_force", 600);
  //     me->add("max_mana",600);
  //     me->add("maximum_mana",600);
  //     me->add("combat_exp",10000) ;
  //     me->add("daoxing",20000);


   message_vision(HIC "$NС������Ĵ��˼���Ʒ��һ�䵭��ɫ�ľջ�Ʈ����$N�����ϡ�$N��ʱ����ԼԼ�о�Ǳ�ܵõ��˼�����\n" NOR);
  tell_object(me,HIG "���С������Ķ�������˵����������ɨĹ�����ˣ�������һ���Ǳ�ܺ�һ�䵭�������㣬addoil!\n"NOR);
//ɾ���ϴ����������ɵĲ��������ӱ��β�����ȷ��ÿλ���ֻ����һ�Ρ�
      me->delete(LAST_PAR + "_sm");
      me->set(THIS_PAR + "_smwl",1);
  } else {
      tell_object(me,HIC "��С������Ĵ��˼���Ʒ���������ֻ��һ��С��: һ��һ�ݣ��������á�\n" NOR);
  }
     destruct(this_object());
     return 1;
}
void owner_is_killed() { destruct(this_object()); }

