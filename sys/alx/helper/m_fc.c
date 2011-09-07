// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";


void create()
{
	set_name("云阳真人", ({"master yunyang", "master", "yunyang"}));
	set("title", "小天师");
	set("long", "云阳真人与菩提祖师实是半师半友，也是三星洞内外总管。\n");
	set("gender", "男性");
	set("age", 70);

	set("str", 30);

	create_family("方寸山三星洞", 2, "蓝");


	SKI->set_list2(_this, FAMILY->skills_of("方寸山三星洞"), 1);

	set_events(
		([
			"born"		: CYN"只听有人喊：何方妖孽，敢欺我门人！",
			"leave"		: CYN"$N叹道：道高一尺，魔高一丈。说罢登云而去。",
	
			"cmds"		: ({ "cast dingshen", "cast light", "cast thunder", "cast fenshen" }),
		])
	);

	setup();

	carry_object("/d/lingtai/obj/xiangpao")->wear();
	carry_object("/d/lingtai/obj/bang")->wield();
}
