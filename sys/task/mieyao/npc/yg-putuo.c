// by firefox 11/21/2009

#include <xyj_x.h>

inherit __DIR__"_base.c";


void set_skills(int level)
{
	string* weapons = ({
		"/d/obj/weapon/staff/budd_staff",
	});

	set("title", "���Ӷ�ɮ");

	SKI->set_list2(_this, FAMILY->skills_of("�Ϻ�����ɽ"), level);

	set("chat_msg_combat", ({
		(: cast_spell, "bighammer" :) })
	);

	carry_object("/d/obj/cloth/shoupiqun")->wear();
	carry_object(random1(weapons))->wield();
}

