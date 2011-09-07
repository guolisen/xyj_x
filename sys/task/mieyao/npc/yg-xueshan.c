// by firefox 11/21/2009

#include <xyj_x.h>

inherit __DIR__"_base.c";


void set_skills(int level)
{
	string* weapons = ({
		"/d/obj/weapon/blade/jindao",
		"/d/obj/weapon/sword/qingfeng"
	});

	set("title", "雪山老妖");

	SKI->set_list2(_this, FAMILY->skills_of("大雪山"), level);

	set("chat_msg_combat", ({
		(: cast_spell, "juanbi" :),
		(: cast_spell,"tuntian.c" :) })
	);

	carry_object("/d/obj/cloth/shoupiqun")->wear();
	carry_object(random1(weapons))->wield();
}

