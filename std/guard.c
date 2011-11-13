// firefox 11/10/2011
// ����

inherit NPC;

#include <xyj_x.h>

//�жϻ�����Ч��
int is_valid(object me, object guard)
{
	return guard->query_temp("invoker") == me
		&& living(guard) && !me->is_fighting(guard);
}

//��ȡ����
object* gards(object me)
{
	object env = environment(me);
	object* arr = ({});
	foreach(object ob in all_inventory(env)) {
		if(is_valid(me, ob))	{
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
/*

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

*/


void copy_status(object leader, object guard)
{
	string* arr = ({
		"title", "nickname", "race", "age", "unit", 
		"str", "int", "con", "per", "cor", "spi", "cps", "kar", 
		"max_kee", "max_sen", "max_force", "max_mana",
		"combat_exp", "daoxing",
	});

	HP->copy_prop(leader, guard, arr, 100);
	HP->copy_skills(leader, guard, 100);
	
	HP->full(guard);
}

void copy_equips(object leader, object guard)
{
	foreach(object o in all_inventory(leader)) {
		if(o->query("equipped")) {
			if(o->query("weapon_prop")) {
				guard->carry_object(base_name(o))->wield();                
			}
			if(o->query("armor_prop")) {
				guard->carry_object(base_name(o))->wear();
			}
		}
	}
}

static object _leader;

//��ʼ����������
int init_jiashen(object guard)
{
	if(!_leader) return 0;
	guard->set_name(_leader->query("name"), _leader->query_my_id());
	copy_status(_leader, guard);
	guard->setup();
	return 1;
}

//���Ƽ���
object clone_jiashen(object leader)
{
	object guard;

	if(!leader) return 0;

	_leader = leader;
	guard = new(__DIR__"jiashen");

	guard->set_temp("invoker", _leader);
	guard->set_leader(_leader);
	copy_equips(_leader, guard);

	guard->move(environment(_leader));
	BTL->copy_enemy(_leader, guard);

	return guard;
}

void test()
{
	object o = clone_jiashen(_player);
	
}