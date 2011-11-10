
inherit NPC;

#include <xyj_x.h>

mapping _npcs = ([
	"½ð¸Õ"			: ({ "jin gang" }),
	"ÏÉÍ¯"			: ({ "xian tong", "tong" }),
	"±ÈÇðÉ®"			: ({ "biqiu seng", "seng" }),

	"Ñ©É½Ñý"			: ({ "xueshan yao", "yao" }),
	"Ð¡×ê·ç"			: ({ "xiao zuanfeng", "yao" }),
	"±ù¹ÈÑ²Ê¹"		: ({"xun shi", "shi"}),
]);


void create()
{
	string name = random1(keys(_npcs));

	set_name(name, _npcs[name]);

	set("per", 11);
	set("gender", "ÄÐÐÔ");
	set("combat_exp", K * K);
	set("daoxing", K * K);


	set("max_kee", 4000);
	set("max_sen", 4000);
	set("max_force", 3000);
	set("max_mana", 3000);

	set_skill("unarmed", 400);
	set_skill("dodge", 400);
	set_skill("parry", 400);

	set("chat_chance", 5);
	set("chat_msg", ({ (: random_move :) }));

	setup();

	carry_object("/d/obj/cloth/linen")->wear();

	if(!random(20))
		carry_object(X_DIR"obj/weapon/quanli")->wield();
}
