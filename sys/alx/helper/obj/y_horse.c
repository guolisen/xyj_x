// by firefox 11/21/2009

inherit NPC;

#include <ansi.h>

void create()
{
	set_name(YEL"����͸����"NOR, ({"yellow dragon", "dragon"}));

	set("long", "һƥ���½ý���ս��ͨ��Ȼƣ�ë����ɫ��\n\n");

	set("race", "Ұ��");
	set("age", 10);
	set("per", 120);

	set("max_kee", 1000000);
	set("max_sen", 1000000);

	set("combat_exp", 2000);
	set("daoxing", 2000);

	set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
	set("verbs", ({ "bite"}));

	set("chat_chance", 1);
	set("ride/msg", "��");

	set_skill("dodge", 1000);

	setup();
}

