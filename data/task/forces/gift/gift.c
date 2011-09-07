//Cracked by Roath
#include <ansi.h>
#define LAST_PAR "sm"
#define THIS_PAR "smwl"
#define GIFT_NAME "节日纪念品"
inherit ITEM;
void create()
{
    set_name(WHT + GIFT_NAME + NOR, ({"gift","liwu"}));
    set_weight(20);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "件");
        set("long",
              HIR+"                ┌──────────────────────┐
                │                                            │ 
                │  "HIY"西游记本站巫师组："HIR"                        │ 
                │                                            │ 
                │   "HIY"    向所有热爱MUD热爱XYJ的玩家致敬"HIR"       │ 
                │                                            │ 
                │   "HIY"         希望你们能够维护本站!  "HIR"         │ 
                │                                            │ 
                │                                            │ 
                │                       "HIW"       addoil!"HIR"       │ 
                │                       "HIY"          麦克小狼"HIR"   │ 
                └──────────────────────┘
北京青岛站巫师组的一点小心意，请打开(chai)来看看是什么？
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


  if (!id(arg))  return notify_fail("你要打开什么？\n");

  if (!me->query(THIS_PAR + "_smwl"))  {
   if(me->query("combat_exp") < 25000) return notify_fail("你的武学还不够25000点。\n"); 
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


   message_vision(HIC "$N小心翼翼的打开了纪念品，一朵淡黄色的菊花飘到了$N的身上。$N顿时隐隐约约感觉潜能得到了激发。\n" NOR);
  tell_object(me,HIG "麦克小狼在你的耳边悄声说道：清明节扫墓辛苦了，这里有一万点潜能和一朵淡菊送与你，addoil!\n"NOR);
//删除上次派礼物生成的参数，增加本次参数，确保每位玩家只能用一次。
      me->delete(LAST_PAR + "_sm");
      me->set(THIS_PAR + "_smwl",1);
  } else {
      tell_object(me,HIC "你小心翼翼的打开了纪念品，结果发现只有一排小字: 一人一份，多领无用。\n" NOR);
  }
     destruct(this_object());
     return 1;
}
void owner_is_killed() { destruct(this_object()); }

