// by firefox 11/21/2009

inherit NPC;

void create()
{
	set_name("��", ({"horse", "ma"}));

	set("long", "һƥ��\n\n");

	set("race", "Ұ��");
	set("age", 10);
	set("per", 120);

	set_skill("dodge", 1000);
	set("combat_exp", 5000);
	set("daoxing", 5000);

	set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
	set("verbs", ({ "bite"}));
	set("chat_chance", 1);

	set("ride/msg", "��");
	set("ride/dodge", 40);

	setup();
}
