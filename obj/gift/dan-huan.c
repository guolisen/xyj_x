// by firefox 11/12/2010

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"gift";

void create()
{
	set_name(HIY"还丹"NOR, ({"huan dan" }));
	
	set("long", "道家合九转丹与朱砂再次提炼而成的仙丹。\n\n");
	set("rewards", ([ DEXP : 100*K ]));
	set("eat_msg", "$N服下一粒$n，顿觉飘飘欲仙。\n\n");

	setup();
}

