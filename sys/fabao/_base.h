// by firefox 11/21/2009
// 法宝基类

#include <xyj_x.h>
#include <ansi.h>

#define LEAVE_LIFE		10		//离开主人的存活时间
#define PET_REI_EXP		(1*M)	//宠物的转世所需经验
#define FABAO_EXP_X		10		//法宝经验系数

mapping _subs;					//物种子类
mapping _trais;					//特征
mapping _act;					//法宝动作
mapping _owner;					//法宝主人
mapping _exp;					//法宝经验

mapping _tab = ([				//exp到属性的兑换表
	"force"		: ({10, 20}),
	"spells"	: ({10, 20}),
	"dodge"		: ({10, 20}),
	"parry"		: ({10, 20}),
	"armor"		: ({20, 10}),
	"damage"	: ({0, 10}),	//初始M点伤害，每兆经验增加N点伤害
]);

void on_wound(object owner, object attacker);	//主人受到伤害

//得到随机子类
string random_name()
{
	return random1(keys(_subs));
}


//法宝不再主人身上，一段时间后消失
void init()
{
	//$N化作一道青光，破空而去。
	//一道霞光/青光/飞入$N宝囊中。
	if(is_character() && !same_env(_this, _owner)
		|| !is_character() && _owner != _env)
	{
		BUFF->start_life(_this, LEAVE_LIFE);
	}
	else if(_act) add_action("do_ji", "ji");
}

//辅助初始化
void setup()
{
	if(!is_character()) {
		set("no_stock", 1);		//禁止储存

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

/*****************************设置属性*****************************/

//设置初始属性
private void set_prop(string name)
{	
	mapping m = _trais["prop"];
	if(m) {
		foreach(string k, mixed v in m) {
			_this->set(name + "/" + k, v);
		}
	}
}

//设置按比例增加属性
private void set_prop_x(string name)
{
	//设置百分比属性
	mapping m = _trais["prop_x"];
	if(m) {
		foreach(string k, mixed v in m) {
			int* arr = _tab[k];
			int v1 = arr[0] + v * _exp / 100 * arr[1] / M;
			_this->add(name + "/" + k, v1);
		}
	}
}

///设置法宝并交给主人
void to_owner(object who, mapping info)
{
	//设置子类信息
	mapping sub = _subs[info["name"]];
	_exp = info["exp"];						//法宝的经验

	//描述信息
	set_name(color_name(info["name"], sub["color"]), sub["ids"]);
	set("long", "\n" + sub["long"] + "\n");
	if(sub["unit"]) set("unit", sub["unit"]);

	//设置属性
	if(!is_character()) {
		if(is_weapon(_this)) {				//武器
			set_prop("weapon_prop");
			set_prop_x("weapon_prop");
		} else if(is_armor(_this)) {		//防具
			set_prop("armor_prop");
			set_prop_x("armor_prop");
		}
		move(who);
	} else {
		if(is_horse(_this)) {		//坐骑
			set_prop("ride");
			set_prop_x("ride");
		} else {					//宠物，某种真身
			call_pet(who, sub["ids"][0], info["name"]);
		}
		move(environment(who));		
	}
	if(_traits["come_msg"]) msv(_traits["come_msg"], who, _this);
}

///召唤宠物
void call_pet(object who, string id, string name)
{
	int n = 1 + _exp / PET_REI_EXP;		//计算宠物转世次数
	//复制状态
	HP->copy_status(who, _this); 
	//设置/启动真身
	RACE_D->set(_this, id, name, n);
	RACE_D->zhenshen(_this);
	set_leader(who);
}

/*****************************法宝生死*****************************/

void heart_beat()
{
	::heart_beat();	//this_object可能在这里就挂了
	if(!_this || !_owner) return;
	if(_owner->is_fighting()) {
		//复制主人的敌人
		if(is_character() && !is_horse(_this)) BTL->copy_enemy(_owner, _this);
		//主人受伤
		if(_this->query("equipped")) {
			object attacker = _owner->query_temp("last_damage_from");
			function fun = _trais["on_wound"];
			if(attacker && fun) evaluate(fun, _owner, attacker);
		}
	}
}


//生物可以死，宝物无意义
void die()
{
	if(_env) msv(_traits["leave_msg"] + "\n\n", _this);
	destruct
}

void unconcious()
{
	die();
}

/*****************************祭出法宝*****************************/

int ji_success(object who, object target, int fabao_exp);

//对单一目标
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


//法宝目标 敌人，双方，环境
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
	BUFF->start_cd(who, _act["cd_id"], name() + "冷却", _act["cd"]);

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


