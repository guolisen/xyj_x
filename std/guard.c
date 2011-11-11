// firefox 11/10/2011
// ����

inherit NPC;

#include <xyj_x.h>

//�жϻ�����Ч��
int is_valid(object me, object guard)
{
	return guard->query_temp("invoker") == me
		&& living(guard) && !me->is_fighting(guard));
}

//��ȡ����
object* gards(object me)
{
	object env = environment(me);
	object* arr = ({});
	foreach(object ob in all_inventory(env)) {
		if(is_valid(me, ob)	{
			arr += ({ob});
		}
	}
	return arr;
}


void create()
{
	set_name("����", ({"jiashen"}));
	set("gender","����");

	set("age",30);
	set("str",30);
	set("per",20);
	set("combat_exp",1000);
	set("daoxing",1000);
        set("attitude", "friendly");
	set_skill("dodge",10);
	set_skill("moshenbu",10);
	map_skill("dodge","moshenbu");

	setup();
}


void call()
{
	if(me->query("mana") < cost)
		return notify_ok("��ķ��������ˣ�\n");

	if(!cd_start(me, "invoke", CD)) 
		return notify_ok("��ոշֹ����ٷ����Σ�գ�\n");

	message("vision",
		RED "ֻ��ž����һ����һ�ź�ⱬ�����ֳ�һ���������ִ���ȵĽ�ա�\n\n"
		+ name() + "˵����ĩ������ٻ�������������\n" NOR,
		environment(), this_object() );
}


void invocation(object leader)
{
	object me = this_object();

	set_temp("invoker", leader);
	set_leader(leader);

	foreach(object enemy in leader->query_enemy()) {
		if(enemy && living(enemy)) {
			kill_ob(enemy);
			if(userp(enemy)) enemy->fight_ob(me);
			else {
				enemy->kill_ob(me);
				enemy->kill_ob(leader);
			}
		}
	}
}

int do_follow(object leader, object target)
{
}

int do_kill(object leader, object target)
{

}

int protect(object leader, object target)
{

}



void die()
{
	message_vison(query("leave_msg"), this_object());
	destruct(this_object());
}


