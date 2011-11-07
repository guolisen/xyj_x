// by firefox 03/27/2010

#include <xyj_x.h>
#include <ansi.h>

inherit NPC;
inherit F_LIFE;

#define LEAVE_MSG		HIB"$N����һ�Σ����һ������ɢȥ�ˡ�\n"NOR

int _other_damage = 0;		//������������˺�
string* _death_msg = ({
	"$n�ȵ����������һ���������ȥ�ɣ�\n$N�ۼ����Σ�ֻ�û��ɹ����̸�����$n�����С�\n",
	"$Nһ������$n�Ķ��֣�ֻ�þ͵�һ�������ԭ�Σ����˼���ת������ʵʵ���߿��ˡ�\n",	
});

/********************************�Ѷ�ϵ��***********************************/
			
//�����Ҫ�ص�ϵ��(%)
mapping calc_coef(object ob, int level)
{
	int n = (level - 5) * 5 + 100;	//[-80%,120%]
	mapping c = ([
		"skill"		: n,
		"exp"		: n,
		"dx"		: n,
		"kee"		: n * 3 / 2,
		"sen"		: n * 3 / 2,
		"force"		: n - 20,
		"mana"		: n - 20,
		"f_factor"	: 10,
		"m_factor"	: 10,
		"chance"	: 5 + level / 2,	//ʩ������
	]);
	return c;
}

void create()
{
	mixed* arr = GNAME->pick(3);
	set_name(arr[0], arr[1]);	

	set("chat_chance", 5);
	set("chat_msg", ({ (: random_move :) }) );

	set("age", 20 + random(80));
	set("class", "yao");

	set_temp("apply/armor", 25);

	set("limbs", ({
		"ͷ��", "����", "�ؿ�", "����", "���", "�Ҽ�", "���",
		"�ұ�", "��צ", "��צ", "����", "С��", "ǰ��", "����",
		"ǰצ", "��צ" })
	);

	//�����Ը�����
	{		
		mapping type = ([
			"normal"		: 7,
			"kill_owner"	: 2,
			"follow_owner"	: 1,		
		]);

		set("type", roulette(type));
		set("env/wimpy", random(20) ? 1 : 20);
	}

	setup();

	life_start(1800, LEAVE_MSG);
}

/********************************��Ϊ��ֹ***********************************/

private void kill_owner(object who)
{
	if(!query("announced")) {
		msv("$N����$n�����һ���������������������⣡\n", _this, who);
		set("announced", 1);
	}
	kill_ob(who);
	who->kill_ob(_this);
}

void init()
{
	string type = query("type");

	if(!living(_this) || !living(_player)) return;

	::init();

	if(query("owner") == _player->query("id")) {
		switch(type) {
		case "follow_owner":
			kill_owner(_player);
			set_leader(random(4) ? _player : 0);
			break;
		case "kill_owner":
			kill_owner(_player);
			break;
		}
	}
		
	remove_call_out("check_room");
	call_out("check_room", 2);
}

int check_room()
{
	object env = environment();

	if(life_check_end()) return 1;

	if(!_this || !living(_this)) return 1;
	if(env && (env->query("no_fight") || env->query("no_magic"))) {
		random_move();
	}
	return 1;
}

void leave()
{
	msv(LEAVE_MSG, _this);
	destruct(_this);
}

/********************************״̬�趨***********************************/

// here should be this NPC specific skills.
void set_skills(int level)
{
}

//����������״̬
void copy_status(object me, object ob, int level)
{
	mapping c = calc_coef(ob, level);
	int max_kee = ob->query("max_sen") * c["kee"] / 100;
	int max_sen = ob->query("max_kee") * c["sen"] / 100;
	int exp = ob->query("combat_exp") / 100 * c["exp"];
	int force = ob->query("max_force") * c["force"] / 100;
	int mana = ob->query("max_mana") * c["mana"] / 100;
	int skill = SKI->max_level(ob) * c["skill"] / 100;
	
	set_skills(skill);

	me->set("combat_exp", exp);
	me->set("daoxing", eff_dx(ob) / 100 * c["dx"]);
	
	me->set("max_kee", max_kee);
	me->set("max_sen", max_sen);
	me->set("max_force", force);
	me->set("max_mana", mana);
	HP->full(me);

	me->set("force_factor", me->query("force_factor") * c["f_factor"] / 100);
	me->set("mana_factor", mana / 20 * c["m_factor"] / 100);

	me->set("chat_chance_combat", c["chance"]);

	me->add_temp("apply/armor", exp / K / K * 5);
}

//����������Ϣ
void set_desc()
{
	mixed* tab = ({
		({10, "СС"}), ({100, "ʮ��"}), ({K, "����"}), ({10*K, "ǧ��"}), ({K*K, "����"}) 
	});
	int dx = query(DEXP) / K / 10 * 10;
	string desc = "һͷ" + name();

	if(dx >= 10)
		desc += "����������" + chinese_number(dx) + "������С������������������ˡ�\n";
	else
		desc += "������������δ�ѡ�\n";	
	set("long",	desc);
	set("title", MATH->cvt_rang(tab, dx));
}

//����
void invocation(object who, int level)
{
	set("owner", getuid(who));

	copy_status(_this, who, level);
	set_desc();
}

void test()
{
	invocation(_this, 9);
}


/********************************��������***********************************/

void die()
{	
	string id = query("owner");
	object owner = id ? find_player(id) : 0;
	
	object_f task = TASK_GET("mieyao", "mieyao");
	mapping m = owner ? task->data_of(owner) : 0;
	string msg = "$N���ˡ�\n";

	//��Ч����
	if(m && TASK->info_match(m, _this)) {
		//������ɶ�
		int sum = query("max_kee") + query("max_sen");
		int ratio = 100 - 100 * _other_damage/sum;			

		if(same_env(_this, owner) && living(owner))	msg = random1(_death_msg);
		msv(msg, _this, owner);

		task->done(owner, ratio);
	} else {
		msv(msg, _this);
	}

	//����
	TASK_GET("forces", "cien")->drop_sth(environment());

	destruct(_this);
}

void unconcious()
{
	if (query("kee") < 0 || query("sen") < 0) die();
	else ::unconcious();
}

private void receive_x(string type, int damage, object who)
{
	if(!who) return;
	who = BTL->invoker(who);
	if(damage > 0 && who && who->query("id") != query("owner")) {
		_other_damage += damage;
		who->add(PEXP, -1);			//�ͷ�ɱ���˹ֵ���
	}
}

varargs int receive_wound(string type, int damage, object who)
{
	receive_x(type, damage, who);
	return ::receive_wound(type, damage, who);
}

varargs int receive_damage(string type, int damage, object who)
{
	receive_x(type, damage, who);
	return ::receive_damage(type, damage, who);
}

/*****************************�����¼�*****************************/

// This is called in heart_beat() to perform attack action.
int attack()
{
	object opponent;

	clean_up_enemy();
	opponent = select_opponent();

	if( objectp(opponent) ) {
		// if the owner faints, then will not attack and leave. -- mon 3/8/99
		if(opponent->query("id") ==  query("owner") 
			&& userp(opponent)
			&& !living(opponent)
			&& same_env(_this, opponent))
		{
			call_out("leave", 1);
			return 0;
		}

		set_temp("last_opponent", opponent);
		COMBAT_D->fight(_this, opponent);
		return 1;
	} 
	return 0;
}


//���㷿�����ʵ��������
private int count_exits(object env)
{
	int n = 0;
	mapping exits = env->query("exits");
	if(exits) {
		foreach(string exit, mixed room in exits) {
			if(room != env) n++;
		}
	}
	return n;
}

int _heal_times = 200;

int heart_beat()
{
    object me = this_object();
    object env = environment();
	mapping db = me->query_entire_dbase();
    
	::heart_beat();

	if(!random(2) && me && !is_busy() && _heal_times) {
		string act;
		int n = env ? count_exits(env) : 99;		
		
		//λ�����Ż�����У�������
		if(!is_fighting() && (n == 0 || n == 8)) {
			string spell = me->query_skill_mapped("spells");
			
			if(spell == "buddhism" && db["eff_sen"] < db["max_sen"])
				act = "cast heal";

			if(db["eff_kee"] < db["max_kee"])
				act = "exert heal";
		}
		
		if(db["kee"] < db["eff_kee"] * 7 / 10) act = "exert recover";
		else if(db["sen"] < db["eff_sen"] * 7 / 10) act = "exert refresh";

		if(act) { 
			command(act);
			_heal_times--;
			if(total_exp(me) < K*K) _heal_times = 0;
		}
		//do sth.
	}
	return 1;
}

