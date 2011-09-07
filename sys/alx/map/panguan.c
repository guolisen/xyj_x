// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit NPC;
inherit F_GREET;

void create()
{
	set_name(HIW"崔珏"NOR, ({"cui jue", "cui"}));
	set("title", HIW"朱笔判官"NOR);
	set("gender", "男性");
	set("long", "崔判官原是阳世为官，因广积阴德，死后被封为阴间判官。\n");
	set("age", 30);

	setup();

	carry_object("/d/obj/cloth/choupao")->wear();
	carry_object("/d/obj/weapon/sword/panguanbi")->wield();
}

void init()
{
	string msg = HIW"\n崔判官向$n招招手，说道：新来的，你莫乱跑，画了生死簿，我好送你还阳。\n\n"NOR;
	::init();
	greet(_this, _player, msg);
}
