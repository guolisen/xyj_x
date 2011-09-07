//Cracked by Roath
#include <ansi.h>
#define LAST_PAR "sm"
#define THIS_PAR "smwl"
inherit ITEM;
void create()
{
    set_name(HIC"墓碑"NOR, ({ "mu bei","bei"}));
    set_weight(5000000);
    if( clonep() )
        set_default_object(__FILE__);
    else {
        set("unit", "个");
        set("no_get","天上传来一声雷鸣：无知小儿，好好扫墓，休得贪心。");
        set("long","唐太宗为唐朝开国元勋设立的墓碑，后人逢清明节都要来这里(sao mu)以示虔诚。");
        set("value", 0);
        set("material", "stone");
    }
}
void init()
{
    add_action("do_take", "sao");
}
 
int do_take(string arg)
{
       object me,obj;
       me = this_player();
       if( !arg || arg!="mu" ) return notify_fail("你要扫什么？\n");
       if( me->query("combat_exp") < 25000 ) return notify_fail("你的武学不够25000点，还不能扫墓。\n");
 //      return notify_fail("现在没有礼物拿。\n");

       if (me->query(THIS_PAR + "_takepager")) {
       tell_object(me,CYN "麦克小狼的身影突然出现在一阵烟雾之中。\n\n");
       tell_object(me,HIR "麦克小狼一巴掌敲在你手上：你已经扫完墓了，不要太贪心，后面还有人等着呢。\n\n");
       tell_object(me,CYN "只见一阵烟雾过後，麦克小狼的身影已经不见了。\n" NOR);
       return 1;
       }
      obj = new (__DIR__"gift");
      obj->move(me);
       message_vision("$N虔诚的扫墓，心中充满对先人们的敬意，你得到了一份礼物。\n",me );
//每次拣礼物，都将上次的参数消除，增加本次拿的参数。 
       me->delete(LAST_PAR + "_takepager");
       me->set(THIS_PAR + "_takepager",1);
       return 1;
}

