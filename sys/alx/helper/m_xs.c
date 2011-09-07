// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name("白象尊者", ({"baixiang zunzhe", "baixiang", "zunzhe"}));
	set("title", "明王护法");
	set("gender", "男性" );
	set("age", 43);
	set("long", "\n这位白象尊者是有名的大力士。\n");

	set("str", 90);

	create_family("大雪山", 2, "弟子");

	SKI->set_list2(_this, FAMILY->skills_of("大雪山"), 1);

	set_events(
		([
			"born"		: HIW"一声长鸣之后，$N缓缓走来。",
			"leave"		: HIY"一只金翅大鹏飞来，抓住$N者，冲上云霄，无影无踪了。",
			"init"		: HIR"$N说道：这儿有活人！",

			"cmds"		: ({ "cast juanbi", "cast tuntian", "cast juanbi" }),
		])
	);
	setup();

	carry_object("/d/obj/armor/yinjia")->wear();
	carry_object(__DIR__"obj/iceblade2")->wield();
}
