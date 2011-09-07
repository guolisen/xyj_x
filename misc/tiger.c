// by firefox 11/21/2009

inherit NPC;
inherit __DIR__"util";

#include <ansi.h>

void create()
{
	set_name(HIY"��쵻�"NOR, ({"tiger", "hu"}));

	set("long",
"�׶�Բͷ�������Ŀ����ֻ�㣬ֱͦ��ɣ���ʮצ�����������\n"
"�������ڣ������ü������׳����è�Σ���������ţ��������\n"
"��ֱֱ�������������H�H�������\n\n"
);

	set("race", "Ұ��");
	set("age", 10);
	set("per", 120);
	set("str", 120);

	set("max_kee", 1000);
	set("max_sen", 1000);

	set_skill("unarmed", 500);
	set_skill("dodge", 500);

	set("combat_exp", 500000);
	set("daoxing", 500000);

	set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
	set("verbs", ({ "bite", "claw" }) );
	set("chat_chance", 90);

	setup();
}



int leave()
{
	object me = this_object();
	message_vision("$N��������ȥ��\n"NOR, me);
	destruct(me);
	return 1;
}

void die()
{
	leave();
}

void unconcious()
{
	die();
}

int invocation(object leader)
{
	object me = this_object();

	copy_enemy(leader, me);
	me->set_temp("invoker", leader);
	me->set_leader(leader);
	me->move(environment(leader));
}

void heart_beat()
{
    object me = this_object();
	object leader = me->query_temp("invoker");

	::heart_beat();	//this_object����������͹���
	if(same_env(me, leader)) {
		if(leader->is_fighting() && !me->is_fighting()) copy_enemy(leader, me);
		else if(!me->is_fighting() && !random(60)) {
			string* cmds = ({"yawn", "lick " + getuid(leader), });
			me->command(random_1(cmds));
		}
	}
}