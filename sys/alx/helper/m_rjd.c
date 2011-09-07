// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name(HIW"·看看·"NOR, ({"rjdwwwwwmmmmmbtq", "rjd"}));
	set("gender", "男性" );
	set("age", 23);
	set("long", "\n"
		"高人，新手总要请教他，如果ID敲对前没疯的话。有诗为证：\n\n"HIW
		"    R在长江头，Q在长江尾，\n"
		"    日日敲名敲不尽，汗似长江水。\n\n"NOR
	);
	set("title", HIY"就算在你面前你都捕捉不到的隐士"NOR);

	set("per", 120);
	set("str", 150);	
		
	SKI->set_list2(_this, 
		({
			({ "literate" }),
			
			({ "yinfeng-zhua",		"unarmed" }), 	
			({ "lotusmove",			"dodge" }),
			
			({ "lotusforce",		"force" }),
			({ "buddhism",			"spells" }),
		}),
		1
	);

	set_events(
		([
			"born"		: HIW"$N探头探脑的看了看，看看无人注意，蹑手蹑脚走过来",
			"leave"		: HIW"$N看无人搭理，看看天，看看表，一溜小跑，转眼就看不见了。",
	
			"cmds"		: ({ "cast huanying1" }),
		])
	);

	setup();
	carry_object("/obj/loginload/linen")->wear();
}

