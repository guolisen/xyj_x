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

///����״̬
void copy_status(object leader, object guard)
{
	string* props = ({
		"title", "nickname", "race", "unit",
		"age", "life/live_forever", "fake_age",
		"str", "int", "con", "per", "cor", "spi", "cps", "kar", 
		"max_kee", "max_sen", "max_force", "max_mana",
		"combat_exp", "daoxing",
	});
	string* tmp_props = ({ "apply/personality", "env/no_accept" });

	HP->copy_prop(leader, guard, props);
	HP->copy_temp_prop(leader, guard, tmp_props);
	HP->copy_skills(leader, guard, 100);
	HP->full(guard);
}

///����Ŀ����Ѫ/����Ϊn��֮һ
void weaken(object who, int n)
{
	mapping db = who->query_entire_dbase();

	db["max_kee"] /= n;
	db["eff_kee"] = db["max_kee"];
	db["kee"] = db["max_kee"];

	db["max_sen"] /= n;
	db["eff_sen"] = db["max_sen"];
	db["sen"] = db["max_sen"];

	db["force_factor"] /= n;
	db["mana_factor"] /= n;
}

void copy_equips(object leader, object guard)
{
	object* arr = all_inventory(leader);
	for(int i = sizeof(arr) - 1; i > -1; --i) {
		if(arr[i]->query("equipped") && !arr[i]->query_unique()) {
			//trace(o->name());
			if(arr[i]->query("weapon_prop")) {
				object e = new(X_DIR"std/x-weapon");
				e->make_fake(arr[i]);
				e->move(guard);
				e->wield();
			} 
			else if(arr[i]->query("armor_prop")) {
				object e = new(X_DIR"std/x-armor");
				e->make_fake(arr[i]);
				e->move(guard);
				e->wear();
			}
		}
	}
}

static object _leader;

//��ʼ����������(�ɼ���create����)
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

	seteuid(getuid());
	_leader = leader;
	guard = new(X_DIR"std/jiashen");

	guard->set_temp("invoker", _leader);
	guard->set_leader(_leader);
	copy_equips(_leader, guard);

	guard->move(environment(_leader));
	BTL->copy_enemy(_leader, guard);

	_leader = 0;

	return guard;
}

void test()
{
	object o = clone_jiashen(_player);	
}
