// by firefox 03/21/2009

#include <weapon.h>
#include <ansi.h>

inherit WHIP;

void create()
{
        set_name(HIW"龙骨鞭"NOR, ({"longgu whip", "whip"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","一条白森森的龙骨，透着一股妖气。\n");
                set("unit", "条");
                set("value", 500);
				set("no_get", 1);
        }
        init_whip(55);
        setup();
}

