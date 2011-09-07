// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

mapping events = ([
	"born"		: HIM"漫天鲜花飞舞，$N款款飘落。",
	"leave"		: HIW"$N漫卷水袖，奔月飞去。",
	"init"		: 0,
	"kill"		: "要明白你的处境，凡人！",

	"cmds"		: ({ "cast arrow", "cast huimeng", "cast invocation", "perform wuxue" }),
]);


void create()
{
	set_name("嫦娥", ({"chang e", "change", "chang","master"}));
	set("long",
		"西王母的大弟子。早年因帮助丈夫盗取西王母之灵药而\n"
		"与其师势成水火。后得和解并邀西王母出掌月宫一门。\n"
	);
	set("title", "月宫主人");
	set("gender", "女性");

	set("per", 90);
	set("str", 10);

	create_family("月宫", 2, "弟子");

	SKI->set_list2(_this, FAMILY->skills_of("月宫"), 1);

	set_events(
		([
			"born"		: HIM"漫天鲜花飞舞，$N款款飘落。",
			"leave"		: HIW"$N漫卷水袖，奔月飞去。",
			"init"		: 0,
			"kill"		: "要明白你的处境，凡人！",

			"cmds"		: ({ "cast arrow", "cast mihun", "cast shiyue" }),
		])
	);

	setup();

	carry_object("/d/moon/obj/luoyi")->wear();
	carry_object("/d/moon/obj/feijian")->wield();
}
