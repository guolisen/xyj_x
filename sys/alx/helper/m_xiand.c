// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void on_init(object me, object who)
{
	if(!me->is_fighting()) {
		me->command("drink jiu hulu");
	}
}

void create()
{
	set_name("长恨鸽", ({"changhen ge", "pigeon", "ge"}));
	set("gender", "女性" );
	set("age", 23);
	set("long", "\n"
		"一只胖鸽子，不知被谁拔了毛，背上油漆喷涂的字迹还没干：\n\n"HIR
		"    天长地久有时尽，此恨绵绵无绝期。\n\n"NOR
	);
	set("title", HIG"一诺千变"NOR);

	set("per", 120);
	set("str", 150);
	
	SKI->set_list2(_this, 
		({
			({ "literate" }),
			
			({ "yinfeng-zhua",		"unarmed" }), 	
			({ "dragonstep",		"dodge" }),
			
			({ "dragonforce",		"force" }),
			({ "yaofa",		"spells" }),

			({ "huntian-hammer",	"hammer",		"parry" }),
		}),
		1
	);

	set_events(
		([
			"born"		: HIW"$N摇摇晃晃的走过来，含含糊糊说道『白日放鸽需纵酒～』。",
			"leave"		: HIW"$N撒腿跑了，边跑边喊『大家先在这等我，马上就来，不见不散』。",
			"init"		: (: on_init :),
	
			"cmds"		: ({ "cast huanying1" }),
		])
	);
	
	setup();
	{
		object hulu = carry_object("/d/obj/weapon/hammer/jiuhulu");
		hulu->wield();
		hulu->set("liquid/remaining", 1000);
	}
}

