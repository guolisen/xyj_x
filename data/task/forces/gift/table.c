//Cracked by Roath
#include <ansi.h>
#define LAST_PAR "sm"
#define THIS_PAR "smwl"
inherit ITEM;
void create()
{
    set_name(HIC"Ĺ��"NOR, ({ "mu bei","bei"}));
    set_weight(5000000);
    if( clonep() )
        set_default_object(__FILE__);
    else {
        set("unit", "��");
        set("no_get","���ϴ���һ����������֪С�����ú�ɨĹ���ݵ�̰�ġ�");
        set("long","��̫��Ϊ�Ƴ�����Ԫѫ������Ĺ�������˷������ڶ�Ҫ������(sao mu)��ʾ�ϡ�");
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
       if( !arg || arg!="mu" ) return notify_fail("��Ҫɨʲô��\n");
       if( me->query("combat_exp") < 25000 ) return notify_fail("�����ѧ����25000�㣬������ɨĹ��\n");
 //      return notify_fail("����û�������á�\n");

       if (me->query(THIS_PAR + "_takepager")) {
       tell_object(me,CYN "���С�ǵ���ӰͻȻ������һ������֮�С�\n\n");
       tell_object(me,HIR "���С��һ�������������ϣ����Ѿ�ɨ��Ĺ�ˣ���Ҫ̫̰�ģ����滹���˵����ء�\n\n");
       tell_object(me,CYN "ֻ��һ��������ᣬ���С�ǵ���Ӱ�Ѿ������ˡ�\n" NOR);
       return 1;
       }
      obj = new (__DIR__"gift");
      obj->move(me);
       message_vision("$N�ϵ�ɨĹ�����г����������ǵľ��⣬��õ���һ�����\n",me );
//ÿ�μ���������ϴεĲ������������ӱ����õĲ����� 
       me->delete(LAST_PAR + "_takepager");
       me->set(THIS_PAR + "_takepager",1);
       return 1;
}

