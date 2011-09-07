// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name("春三十娘", ({ "chun sanshiniang", "chun", "sanshiniang" }));
	set("gender", "女性" );
	set("age", 23);
	set("long", "\n蜘蛛精\n");
	set("title", "桃花娘子");

	set("per", 90);
	set("str", 10);

	create_family("盘丝洞", 2, "弟子");

	SKI->set_list2(_this, FAMILY->skills_of("盘丝洞"), 1);

	set_events(
		([
			"born"		: HIM"隐约传来『金钱落地，人头不保，桃花过处，寸草不生！』",
			"leave"		: HIM"$N只见口中吐丝，如同风筝一般飘走。",

			"cmds"		: ({ "cast pansi", "cast love", "cast yihun" }),
		])
	);

	setup();

	carry_object("/d/obj/cloth/nichang")->wear();
	carry_object("/d/obj/cloth/yuanxiang")->wear();
	carry_object("/d/obj/weapon/sword/qinghong")->wield();
}
