// firefox 11/21/2009

inherit NPC;

#include <ansi.h>
#include <xyj_x.h>

#define NAME			"����"
#define CD				5

int test_player();

object_f _task = TASK_GET("mieyao", "mieyao");

void create()
{
	set_name(NAME, ({ "di ting", "diting" }) );

	set("title", "��������");
	set("gender", "����" );
	set("race", "Ұ��");
	set("can_speak", 1);
	set("age", 15);
	set("per", 120);
	set("long", "

�����ǵز����������·���һ���ޡ��������ڵ��£�һ��ʱ�����Ĵ�
��ɽ����𢣬���츣��֮�䣬���桢��桢ë�桢��桢���桢���ɡ�
���ɡ����ɡ����ɡ����ɿ����ռ��ƶ񣬲������ޡ�����������⨺���
������ߣ������������棬��ֻ�����ˡ�

");     

	set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
	set("verbs", ({ "bite", "claw" }) );

	set("chat_chance", 1);
	set("chat_msg", ({	NAME"�ú���ץ��ץ�Լ��Ķ��䡣\n" }) );
	set("inquiry", ([
		"mieyao":   (: test_player() :),
	]));

	setup();
}


int test_player()
{
	object me = this_object();
	object who = this_player();
	object ob = _task->query_guai(who);

	if(!cd_start(me, "answer", CD)) {
		msvx(CYN"$N�����۾���װ˯����...\n"NOR, me);
		return 1;
	}

	if(ob) {
		object env = environment(ob);
		if(env) {
			string map = MISC_D->find_place(env);
			string room = env->query("short");
			if(map != room) room = map + "��" + room;

			msvx(CYN"$N�����ڵأ�����̧��ͷ������$n˵��������������%s��\n"NOR, me, who, room);
			return 1;
		}
	}

	msvx(CYN"$N�����ڵأ�����̧��ͷ������$n˵���������޴˹֡�\n"NOR, me, who);
	return 1;
}

void die()
{
	set("eff_kee", 2200);
	set("eff_sen", 2200);
	set("kee", 2200);
	set("sen", 2200);
}

void unconcious()
{
	die ();
}