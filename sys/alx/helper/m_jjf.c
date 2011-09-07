// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name("秦琼", ({ "qin qiong", "qin" }));
	set("title", "左武卫大将军");
	set("long", "秦叔宝是大唐国开国名臣，更是一位出名的武将。\n");
	set("gender", "男性");
	set("age", 43);

	set("str", 40);
	set("cor", 30);
	set_temp("apply/armor", 500);

	create_family("将军府", 2, "蓝");

	SKI->set_list2(_this, FAMILY->skills_of("将军府"), 1);

	set_events(
		([
			"born"		: CYN"滚滚烟尘中，$N策马扬鞭而来。",
			"leave"		: CYN"$N一声大喝，绝尘而去！",
			"init"		: 0,
			"kill"		: "尘归尘，土归土。",

			"cmds"		: ({ "exert jingxin", "perform qiangjian" }),
		])
	);

	setup();

	carry_object(__DIR__"obj/y_bow")->wear();
	carry_object(__DIR__"obj/y_bag")->wear();
	carry_object(__DIR__"obj/y_boots")->wear();
	carry_object(__DIR__"obj/y_waist")->wear();
	carry_object(__DIR__"obj/y_cloth")->wear();
	carry_object(__DIR__"obj/y_armor")->wear();
	carry_object(__DIR__"obj/y_helmet")->wear();
	carry_object(__DIR__"obj/y_mace");
	carry_object(__DIR__"obj/y_spear")->wield();

}

void init()
{
	::init();
}
