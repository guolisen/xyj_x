// by firefox 11/21/2009
// ��������

#include <xyj_x.h>
#include <ansi.h>

#define LEAVE_LIFE		10		//�뿪���˵Ĵ��ʱ��
#define PET_REI_EXP		(1*M)	//�����ת�����辭��
#define FABAO_EXP_X		10		//��������ϵ��

mapping _subs;					//��������
mapping _trais;					//����
mapping _act;					//��������
mapping _owner;					//��������
mapping _exp;					//��������

mapping _tab = ([				//exp�����ԵĶһ���
	"force"		: ({10, 20}),
	"spells"	: ({10, 20}),
	"dodge"		: ({10, 20}),
	"parry"		: ({10, 20}),
	"armor"		: ({20, 10}),
	"damage"	: ({0, 10}),	//��ʼM���˺���ÿ�׾�������N���˺�
]);

void on_wound(object owner, object attacker);	//�����ܵ��˺�

//�õ��������
string random_name()
{
	return random1(keys(_subs));
}


//���������������ϣ�һ��ʱ�����ʧ
void init()
{
	//$N����һ����⣬�ƿն�ȥ��
	//һ��ϼ��/���/����$N�����С�
	if(is_character() && !same_env(_this, _owner)
		|| !is_character() && _owner != _env)
	{
		BUFF->start_life(_this, LEAVE_LIFE);
	}
	else if(_act) add_action("do_ji", "ji");
}

//������ʼ��
void setup()
{
	if(!is_character()) {
		set("no_stock", 1);		//��ֹ����

		set("value", 1);
		set("no_sell", 1);
		set("no_drop", 1);
		set("no_give", 1);
		set("no_put", 1);
		set("no_get", 1);
	}

	set_heart_beat(1);
	::setup();
}

/*****************************��������*****************************/

//���ó�ʼ����
private void set_prop(string name)
{	
	mapping m = _trais["prop"];
	if(m) {
		foreach(string k, mixed v in m) {
			_this->set(name + "/" + k, v);
		}
	}
}

//���ð�������������
private void set_prop_x(string name)
{
	//���ðٷֱ�����
	mapping m = _trais["prop_x"];
	if(m) {
		foreach(string k, mixed v in m) {
			int* arr = _tab[k];
			int v1 = arr[0] + v * _exp / 100 * arr[1] / M;
			_this->add(name + "/" + k, v1);
		}
	}
}

///���÷�������������
void to_owner(object who, mapping info)
{
	//����������Ϣ
	mapping sub = _subs[info["name"]];
	_exp = info["exp"];						//�����ľ���

	//������Ϣ
	set_name(color_name(info["name"], sub["color"]), sub["ids"]);
	set("long", "\n" + sub["long"] + "\n");
	if(sub["unit"]) set("unit", sub["unit"]);

	//��������
	if(!is_character()) {
		if(is_weapon(_this)) {				//����
			set_prop("weapon_prop");
			set_prop_x("weapon_prop");
		} else if(is_armor(_this)) {		//����
			set_prop("armor_prop");
			set_prop_x("armor_prop");
		}
		move(who);
	} else {
		if(is_horse(_this)) {		//����
			set_prop("ride");
			set_prop_x("ride");
		} else {					//���ĳ������
			call_pet(who, sub["ids"][0], info["name"]);
		}
		move(environment(who));		
	}
	if(_traits["come_msg"]) msv(_traits["come_msg"], who, _this);
}

///�ٻ�����
void call_pet(object who, string id, string name)
{
	int n = 1 + _exp / PET_REI_EXP;		//�������ת������
	//����״̬
	HP->copy_status(who, _this); 
	//����/��������
	RACE_D->set(_this, id, name, n);
	RACE_D->zhenshen(_this);
	set_leader(who);
}

/*****************************��������*****************************/

void heart_beat()
{
	::heart_beat();	//this_object����������͹���
	if(!_this || !_owner) return;
	if(_owner->is_fighting()) {
		//�������˵ĵ���
		if(is_character() && !is_horse(_this)) BTL->copy_enemy(_owner, _this);
		//��������
		if(_this->query("equipped")) {
			object attacker = _owner->query_temp("last_damage_from");
			function fun = _trais["on_wound"];
			if(attacker && fun) evaluate(fun, _owner, attacker);
		}
	}
}


//���������������������
void die()
{
	if(_env) msv(_traits["leave_msg"] + "\n\n", _this);
	destruct
}

void unconcious()
{
	die();
}

/*****************************��������*****************************/

int ji_success(object who, object target, int fabao_exp);

//�Ե�һĿ��
private void ji_ob(object who, object target, int fabao_exp)
{
	mapping cmp = ([ ({fabao_exp, target->query(DEXP)/FABAO_EXP_X }) : 5 ]);
	cmp += _act["cmp"];

	if(BTL->random_cmp(who, target, cmp_parm) >= _act["threshold"]) {
		MSG->vision(_act["msg_success"] + NOR"\n", who, target, _this->name());
		ji_success(who, target, fabao_exp);
	} else {
		MSG->vision(_act["msg_fail"] + NOR"\n", who, target, _this->name());
	}
}


//����Ŀ�� ���ˣ�˫��������
int ji(string tid)
{
	object who = _player;
	object target = tid ? present(tid, environment(who)) : 0;
	mapping m = _act["target"];
	int fabao_exp = _act["exp_x"] * _exp / 100;
	object* enemies = BTL->enemies(who);

	if(m["need_enemy"] && !tid) target = BTL->random_enemy();
	if(!BTL->check_target(who, target, m)) return 1;			//??????

	if(!BTL->require(who, NAME, _act["req"])) return 1;
	BTL->pay(me, _act["req"]["prop"]);
	BUFF->start_cd(who, _act["cd_id"], name() + "��ȴ", _act["cd"]);

	MSG->vision(_act["msg_start"] + NOR"\n", who, target, _this->name());

	if(m["need_enemies"]) {
		foreach(object enemy in enemies) {
			ji_ob(who, enemy, fabao_exp);
		}
	} else {
		ji_ob(who, target, fabao_exp);
	}
	return 1;
}


