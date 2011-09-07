// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void on_init(object me, object who)
{
	if(!random(3)) me->command("cast zhua on " + who->query("id"));
}

void create()
{
	set_name("玉鼠精", ({"yu shu","yushu", "shu"}));
	set("gender", "女性" );
	set("age", 23);
	set("long", "\n她就是这无底洞的洞主了。她从修道成人行以来，吃人无数，\n");
	set("title", "地涌夫人");

	set("per", 30);
	set("str", 20);	
	
	create_family("陷空山无底洞", 1, "弟子");

	SKI->set_list2(_this, FAMILY->skills_of("陷空山无底洞"), 1);

	set_events(
		([
			"born"		: HIY"$N突然从地下钻了出来",
			"leave"		: HIY"$N向空中抛了一把土，念句咒，钻入土中不见了。",
			"init"		: (: on_init :),
	
			"cmds"		: ({ "cast huanying", "cast bianfu", "cast suliao"}),
		])
	);

	setup();

	carry_object("/d/obj/cloth/nichang")->wear();
	carry_object("/d/obj/cloth/yuanxiang")->wear();
}

