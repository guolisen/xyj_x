// by firefox 11/21/2009

#include <xyj_x.h>

inherit __DIR__"_base.c";


void set_skills(int level)
{
	string* weapons = ({
		"/d/obj/weapon/hammer/jingua",
		"/d/obj/weapon/fork/gangcha"
	});

	set("title", "Áú¹¬¹ÖÎï");

	SKI->set_list2(_this, FAMILY->skills_of("¶«º£Áú¹¬"), level);

	set("chat_msg_combat", ({
		(: cast_spell, "freez" :),
        (: cast_spell, "breathe" :),
        //(: exert_function, "roar" :),
        (: exert_function, "shield" :) })
	);

	carry_object("/d/obj/cloth/shoupiqun")->wear();
	carry_object(random1(weapons))->wield();
}

