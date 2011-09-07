// by firefox 11/21/2009

#include <xyj_x.h>

inherit __DIR__"_base.c";


void set_skills(int level)
{
	string* weapons = ({
		"/d/sea/obj/dragonwhip",
		"/d/obj/weapon/sword/qingfeng"
	});

	set("title", "月宫魔女");
	set("gender", "女性");

	SKI->set_list2(_this, FAMILY->skills_of("月宫"), level);

	set("chat_msg_combat", ({
		(: cast_spell, "arrow" :) })
	);

	carry_object("/d/obj/cloth/shoupiqun")->wear();
	carry_object(random1(weapons))->wield();
}

