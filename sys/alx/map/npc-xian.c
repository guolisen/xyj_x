// by firefox 11/21/2009
// 仙界领袖

#include <xyj_x.h>

inherit __DIR__"npc-base";

void create()
{
	set_name("文殊菩萨", ({"wenshu pusa", "pusa"}));
	
	set("long", "

释迦牟尼佛的左胁侍菩萨，代表聪明智慧。因德才超群，居菩萨之首。

"
	);
	set("title", "南无大智");
	set("gender", "男性");
	set("age", 40);	
	set("per", 30);

	SKI->set_list(this_object(), ({
		({ "literate",		120, }),
		({ "liangyi-sword",	200,	"sword",	180,	"parry",	180 }),
		({ "buddhism",		200,	"spells",	200 }),
		({ "lotusforce",	180,	"force",	180 }),
		({ "lotusmove",		180,	"dodge",	180 }),
	}));

	set("chat_msg_combat", ({
		(: cast_spell, "bighammer" :),
		})
	);

	setup();

	carry_object("/d/obj/cloth/jia_sha")->wear();
	//carry_object(__DIR__"obj/zq-sword")->wield(); 慧剑

}
