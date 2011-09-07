// by firefox 08/16/2010

#include <xyj_x.h>

inherit ITEM;
inherit F_LIFE;

//以下选自玄奘的大乘经部分，挑字少的
string* _names = ({
	"菩萨藏经",
	"解深密经",
	"甚希有经",
	"天请问经",
	"最无比经",
	/*"无垢称经",
	"本事经",
	"大般若经",
	"缘起经",
	"咒五首经",*/
});

void create()
{
	set_name(random1(_names) + "残片", ({"can pian", "pian", "debris"}));
		
	set("no_give", 1);

	if(clonep())
		set_default_object(__FILE__);
	else {
		set("long","一片经文的残片，字迹已经模糊，看来浸过水。\n");
		set("unit", "片");


		set("no_put", 1);
		set("no_drop", 1);
		set("no_stock", 1);
	}
	setup();

	set_heart_beat(30);
	life_start(600);
}


void heart_beat()
{
	life_check_end();
}

