// by firefox 11/21/2009

inherit NPC;

#include <ansi.h>

void create()
{
	set_name(YEL"黄骠透骨龙"NOR, ({"yellow dragon", "dragon"}));

	set("long", "一匹骁勇矫健的战马，通体橙黄，毛无杂色。\n\n");

	set("race", "野兽");
	set("age", 10);
	set("per", 120);

	set("max_kee", 1000000);
	set("max_sen", 1000000);

	set("combat_exp", 2000);
	set("daoxing", 2000);

	set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
	set("verbs", ({ "bite"}));

	set("chat_chance", 1);
	set("ride/msg", "骑");

	set_skill("dodge", 1000);

	setup();
}

