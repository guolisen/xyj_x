// firefox 2011.11
// 拳利

#include <weapon.h>

inherit KNUCKLES;

void create()
{
	set_name("拳利", ({"quan li", "knuckles"}));
	set_weight(500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long","拳套上安装着利刃，始于春秋，亦称拳刺、拳剑或拳刃。\n");
		set("unit", "把");
		set("value", 1000);
	}
	init_knuckles(26, EDGED);
	setup();
}

