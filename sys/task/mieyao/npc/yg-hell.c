// by firefox 11/21/2009

#include <xyj_x.h>

inherit __DIR__"_base.c";


void set_skills(int level)
{
	string* weapons = ({
		"/d/obj/weapon/stick/xiangmo",
		"/d/obj/weapon/whip/tielian"
	});

	set("title", "ÓÄÚ¤¶ñ¹í");

	SKI->set_list2(_this, FAMILY->skills_of("ÑÖÂÞµØ¸®"), level);

	set("chat_msg_combat", ({
		(: perform_action, "whip", "three" :),
        //(: cast_spell, "gouhun" :),
        (: exert_function, "sheqi" :) })
	);

	carry_object("/d/obj/cloth/shoupiqun")->wear();
	carry_object(random1(weapons))->wield();
}

