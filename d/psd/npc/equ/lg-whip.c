// by firefox 03/21/2009

#include <weapon.h>
#include <ansi.h>

inherit WHIP;

void create()
{
        set_name(HIW"���Ǳ�"NOR, ({"longgu whip", "whip"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","һ����ɭɭ�����ǣ�͸��һ��������\n");
                set("unit", "��");
                set("value", 500);
				set("no_get", 1);
        }
        init_whip(55);
        setup();
}

