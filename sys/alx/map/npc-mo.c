// by firefox 11/21/2009
// �ɽ�����

#include <xyj_x.h>

inherit __DIR__"npc-base";

void create()
{
	set_name("��ʨ����", ({"qingshi daiwang", "daiwang"}));
	
	set("long", "

��ʨ������ʨ����󵱼ң���������������

"
	);
	set("title", "ʨ����");
	set("gender", "����");
	set("age", 40);
	set("per", 9);

	SKI->set_list(this_object(), ({
		({ "literate",		120, }),
		({ "bingpo-blade",	200,	"blade",	180,	"parry",	180 }),
		({ "dengxian-dafa",	200,	"spells",	200 }),
		({ "ningxie-force",	180,	"force",	180 }),
		({ "xiaoyaoyou",	180,	"dodge",	180 }),
	}));

	set("chat_msg_combat", ({
		(: cast_spell, "hufa" :),
		})
	);

	setup();

	carry_object("/d/obj/armor/jinjia")->wear();
	//carry_object(__DIR__"obj/zq-sword")->wield(); �۽�

}
