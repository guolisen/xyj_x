// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

void create()
{
	set_name("阎罗王", ({"yanluo wang","wang", "master", "yanluo"}));
	set("long", "\n身穿大红蟒袍，头戴黑绸软巾．面如锅底，须若钢针，这就是阎罗王．\n");
	set("title", "阴间十王之");
	set("class", "youling");
	set("gender", "男性");
	set("age", 50);

	create_family("阎罗地府", 2, "你好");

	SKI->set_list2(_this, FAMILY->skills_of("阎罗地府"), 1);

	set_events(
		([
			"born"		: HIB"一阵黑风骤起，$N出现在众人面前。",
			"leave"		: HIB"$N口中喷出一股黑风，整个人也随着黑风散去。。。",
			"init"		: CYN"$N说道：天堂有路你不走，地狱无门自来投！",
			"kill"		: 0,

			"cmds"		: ({ "cast inferno", "cast gouhun" }),
		])
	);

	setup();

	carry_object("/d/obj/cloth/mangpao")->wear();
	carry_object("/d/obj/weapon/sword/qinghong")->wield();
}
