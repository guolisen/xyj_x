// by firefox 11/21/2009

#include <xyj_x.h>

inherit __DIR__"_base.c";


void set_skills(int level)
{
	string* weapons = ({
		"/d/obj/weapon/hammer/jingua",
		"/d/obj/weapon/sword/qingfeng"
	});

	set("title", "��ׯ����ͽ");

	SKI->set_list2(_this, FAMILY->skills_of("��ׯ��"), level);

	set("chat_msg_combat", ({
		(: cast_spell, "zhenhuo" :) })
	);

	carry_object("/d/obj/cloth/shoupiqun")->wear();
	carry_object(random1(weapons))->wield();
}

