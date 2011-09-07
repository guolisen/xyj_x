// by firefox 11/12/2010

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"gift";

void create()
{
	set_name(YEL"九转金丹"NOR, ({"jiuzhuan jindan", "jindan" }));
	
	set("long", "应四时而采取药物，养九转而修炼丹成。\n\n");
	set("rewards", ([ DEXP : 10*K ]));
	set("eat_msg", "$N服下一粒$n，顿觉飘飘欲仙。\n\n");

	setup();
}

