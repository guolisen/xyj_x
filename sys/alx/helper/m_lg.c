// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name("敖广", ({"ao guang", "ao","guang","longwang","wang"}));

	set("long", "/n敖广是东海的龙王，其兄弟分别掌管东，西，南，北四海。\n");
	set("gender", "男性");
	set("age", 66);
	set("title", "东海龙王");
	set("class","dragon");

	create_family("东海龙宫", 1, "水族");

	SKI->set_list2(_this, FAMILY->skills_of("东海龙宫"), 1);

	set_events(
		([
			"born"		: HIW"一阵电闪雷鸣，$N出现在众人面前。",
			"leave"		: HIW"$N的脚下突然涌起一股水波，水流过后，$N随之不见了！",
			"init"		: 0,
			"kill"		: "这就是好奇的代价！",

			"cmds"		: ({ "cast freez", "cast water" }),
		])
	);

	setup();

	carry_object("/d/sea/obj/longpao")->wear();
}
