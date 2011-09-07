// by firefox 11/21/2009

inherit NPC;

void create()
{
	set_name("马", ({"horse", "ma"}));

	set("long", "一匹马。\n\n");

	set("race", "野兽");
	set("age", 10);
	set("per", 120);

	set_skill("dodge", 1000);
	set("combat_exp", 5000);
	set("daoxing", 5000);

	set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
	set("verbs", ({ "bite"}));
	set("chat_chance", 1);

	set("ride/msg", "骑");
	set("ride/dodge", 40);

	setup();
}
