// by firefox 11/21/2009

#include <xyj_x.h>

inherit __DIR__"_base.c";


void set_skills(int level)
{
	string* weapons = ({
		"/d/obj/weapon/axe/huafu",
		"/d/obj/weapon/spear/changqiang"
	});

	_this->set("title", "将军府叛将");

	SKI->set_list2(_this, FAMILY->skills_of("将军府"), level);

	set("chat_msg_combat", ({
//        (: perform_action, "axe", "sanban" :),
        (: exert_function, "jingxin" :) })
	);

	carry_object("/d/obj/cloth/shoupiqun")->wear();
	carry_object(random1(weapons))->wield();
}

