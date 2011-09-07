// by firefox 11/21/2009

#include <xyj_x.h>

inherit __DIR__"_base.c";


void set_skills(int level)
{
	string* weapons = ({
		"/d/obj/weapon/stick/xiangmo",
		"/d/obj/weapon/sword/qingfeng"
	});

	set("title", "方寸妖道");

	SKI->set_list2(_this, FAMILY->skills_of("方寸山三星洞"), level);

	set("chat_msg_combat", ({
		(: perform_action, "stick", "pili" :),
        (: perform_action, "stick", "qiankun" :),
        (: cast_spell, "thunder" :),
        (: cast_spell, "light" :),
        (: cast_spell, "dingshen" :) })
	);

	carry_object("/d/obj/cloth/shoupiqun")->wear();
	carry_object(random1(weapons))->wield();
}

