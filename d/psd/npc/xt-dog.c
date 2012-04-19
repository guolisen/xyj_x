// by firefox 03/21/2009

inherit NPC;

#include <xyj_x.h>
#include <ansi.h>

void create()
{
	set_name("Х��Ȯ", ({ "xiaotian quan", "quan" }) );
	set("race", "Ұ��");
	set("age", 3);
	set("long", "һֻ���ú����˵Ķ񹷡�������ͷ�����ſ�ˮ��\n");
	
	set("per", 100);
	set("str", 200);
	set("dex", 36);
	set("gender", "����");

	set("combat_exp", 1000*K);
	set("daoxing", 1000*K);

	set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
	set("verbs", ({ "bite", "claw" }) );

	set("chat_chance", 6);
	set("chat_msg", ({
		CYN"Х��Ȯ������̧��ͷ��\n"NOR,
	}) );
		
	set_temp("apply/attack", 300);
	set_temp("apply/armor", 300);

	setup();
}


void die()
{
	if(environment()) message_vision(CYN"\n\n$N�ҽ�һ��������β���ܵ��ˡ�\n\n"NOR, _this);
	destruct(this_object());
}

/*****************************�Ĵ�����*****************************/

int mount_dog()
{
	object me = this_object();
	string* arr = ({
		"/d/ourhome/npc/dog",
		"/d/city/npc/dog",
		"/d/lingtai/npc/oldwolf",
	});
	string str = random1(arr);
	object* dogs = children(str);

	if(sizeof(dogs)) {
		object dog = random1(dogs);
		object env = environment(dog);
		if(env && me->move(env)) {
			dog->set_temp("ride_msg", "��");
			dog->set_temp("ride_prop/dodge", 1);
			dog->set("gender", "����");
			me->command("mount " + dog->query("id"));
		}
	}
	return 1;
}

void debut()
{
	mount_dog();
}