// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name("净瓶使者", ({ "shizhe" }));
	set("title", "南海观音侍从");   
	set("long", "\n南海观音座前净瓶使者。\n");
	set("gender", "男性");
	set("age", 20);

	create_family("南海普陀山", 2, "弟子");
	
	SKI->set_list2(_this, FAMILY->skills_of("南海普陀山"), 1	);

	set_events(
		([
			"born"		: HIY"$N从天而降。",				
			"leave"		: HIY"$N驾祥云，登彩雾，径往西方去了。。。",

			"cmds"		: ({ "cast heal", "cast bighammer", "cast yinshen" }),
		])
	);

	setup();

	carry_object("/obj/cloth")->wear();
	carry_object("/d/nanhai/obj/budd_staff")->wield();
}
