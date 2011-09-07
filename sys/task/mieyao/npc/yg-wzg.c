// by firefox 11/21/2009

#include <xyj_x.h>

inherit __DIR__"_base.c";


void set_skills(int level)
{
	string* weapons = ({
		"/d/obj/weapon/hammer/jingua",
		"/d/obj/weapon/sword/qingfeng"
	});

	set("title", "五庄观凶徒");

	SKI->set_list2(_this, FAMILY->skills_of("五庄观"), level);

	set("chat_msg_combat", ({
		(: cast_spell, "zhenhuo" :) })
	);

	carry_object("/d/obj/cloth/shoupiqun")->wear();
	carry_object(random1(weapons))->wield();
}

