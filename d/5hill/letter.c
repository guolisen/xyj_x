//邀请玩家的凭证。符合原著。
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIY"鬼画符开启封印"NOR, ({"feng yin", "yin", "seal"}));
	set("weight", 5);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","一条黄绢，上面画着白菡萏、青莲花、红芙蕖，阿褥多罗三藐三菩提，一排小字：乾坤屯需蒙，急急如律令。\n");
		set("unit", "条");
		set("no_get", 1);
		set("no_give", 1);
	}
	set("channel_id", "取经系统");
	setup();
}

