// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

#define BUSY					1
#define NO_MOVE					1
#define FIGHTING				1
#define DOTING					1


//检查技能前提条件
int require(object target, string name, mapping req)
{
	if(req["ex_temp"]) {	//检查互斥技能的临时标记
		foreach(string k, mixed v in req["ex_temp"]) {
			if(target->query_temp(k)) {
				if(stringp(v)) {
					printf(v + "\n");
				} else {
					printf("你还不能施放" + name + "。\n");
				}
				return 0;
			}
		}
	}
	if(req["ex_value"]) {	//检查互斥技能的标记
		foreach(string k, mixed v in req["ex_value"]) {
			if(target->query(k)) {
				if(stringp(v)) printf(v + "\n");
				else printf("你还不能施放" + name + "。\n");
				return 0;
			}
		}
	}
	if(req["ex_class"]) {	//检查某类互斥buff
		foreach(string k, mixed v in req["ex_class"]) {
			if(BUFF->find2(target, k)) {
				if(stringp(v)) printf(v + "\n");
				else printf("目标上已经存在" + k + "。\n");
				return 0;
			}
		}
	}
	if(req["skill"]) {		//检查skill要求
		foreach(string k, int v in req["skill"]) {
			int lvl = target->query_skill(k);
			if(lvl < v) {
				printf("你的修为不足以施放" + name + "。\n");
				return 0;
			}
		}
	}
	if(req["skill1"]) {		//检查skill要求
		foreach(string k, int v in req["skill1"]) {
			int lvl = target->query_skill(k, 1);
			if(lvl < v) {
				printf("你的修为不足以施放" + name + "。\n");
				return 0;
			}
		}
	}
	if(req["skill_map"]) {	//检查skill map
		foreach(string k, int v in req["skill_map"]) {			
			if(target->query_skill_mapped(k) != v) {
				printf("你必须激发" + to_chinese(v) + "才能施放" + name + "。\n");	//TODO:名字
				return 0;
			}
		}
	}
	if(req["prop"]) {		//检查状态数值
		foreach(string k, int v in req["prop"]) {
			int n = target->query(k);
			if(n < v) {
				printf("你状态不佳，无力施放" + name + "。\n");
				return 0;
			}
		}
	}
	if(req["cd"]) {			//检查技能冷却
		foreach(string k, int v in req["cd"]) {
			if(BUFF->query_cd(target, k)) {
				printf("你需要过一段时间才能施放" + name + "。\n");
				return 0;
			}
		}
	}
	return 1;
}

//检查不良状态
string bad_state(object target, string* status)
{
	foreach(string s in status) {
		if(s == "busy" && (target->is_busy() 
			|| target->query_temp("pending/exercising"))) {
			return "现在正忙着呢";
		}
		else if(s == "fighting" && target->is_fighting()) {
			return "正在打架，无暇旁骛";
		}
		else if(s == "no_move" && target->query_temp("no_move")) {
			return "无法移动";
		}
		else if(s == "ghost" && target->is_ghost()) {
			return "是鬼魂";
		}
		else if(s == "invisible" && target->query("env/invisibility")) {
			return "在隐身中";
		}
	}
	return 0;
}

//获取目标的召唤者
object invoker(object who)
{
	object inv;		
	while(who && inv = who->query_temp("invoker")) who = inv;	//多级召唤
	return who;
}

//全部敌人
object* enemies(object me)
{
	me->clean_up_enemy();
	return me->query_enemy();
}

//随机选择仇人
object random_enemy(object me)
{
	object* arr = enemies(me);
	return sizeof(arr) ? random1(arr) : 0;
}

//是否可攻击目标
int can_attack(object me, object target)
{
	if(!target
		|| !target->is_character()
		|| target->is_corpse()
		|| target == me)
		return 0;
	return 1;
}

//检查目标是否满足条件
int check_target(object me, object target, mapping m)
{
	object env = environment(target);

	if(m["need_target"] && !target) return notify_fail("必须指定一个目标。\n");
	if(m["need_enemy"] && (!target || !me->is_fighting(target)))
		return notify_fail("必须指定一个敌对目标。\n");
	if(m["need_enemies"] && !sizeof(enemies(me)))
		return notify_fail("没有敌对目标。\n");
	if(m["need_kill"] && !target->is_killing(me))
		return notify_fail("对方与你并无深仇大恨。\n");
	if(m["need_living"] && !living(target))
		return notify_fail("必须指定一个活物作目标。\n");
	if(m["need_no_busy"] && target->is_busy())
		return notify_fail("目标自顾不暇，不必多此一举。\n");
	if(m["can_move"] && is_no_move(target))
		return notify_fail("目标无法移动，不必多此一举。\n");
	if(m["can_fight"] && !(env->query("no_fight") || env->query("no_magic")))
		return notify_fail("目标处于安全区。\n");
	return 1;
}

//获取可攻击目标，如果无target，则随机选择
object get_victim(object me, object target)
{
	if(!target) target = random_enemy(me);
	if(!can_attack(me, target))	return 0;
	return target;
}

//支付技能成本
void pay(object target , mapping cost)
{
	foreach(string k, int v in cost) {
		target->add(k, -v);
	}
}

//获取后天天赋
int query_attr(object target, string attr)
{
	if(attr == "str" || attr == "strength") {
		return target->query_str();
	}
	else if(attr == "cor" || attr == "courage") {
		return target->query_cor();
	}
	else if(attr == "int" || attr == "intelligence") {
		return target->query_int();
	}
	else if(attr == "spi" || attr == "spirituality") {
		return target->query_spi();
	}
	else if(attr == "cps" || attr == "composure") {
		return target->query_cps();
	}
	else if(attr == "per" || attr == "personality") {
		return target->query_per();
	}
	else if(attr == "con" || attr == "constitution") {
		return target->query_con();
	}
	else if(attr == "kar" || attr == "karma") {
		return target->query_kar();
	}
	else if(attr == "dodge") {					//轻功
		return target->query_skill("dodge");
	}
	else if(attr == "attack") {					//攻击技能
		object weapon = target->query_temp("weapon");
		string skill = weapon ? weapon->query("skill_type") : "unarmed";
		return target->query_skill(skill);
	}
	return 0;
}

//a与b的比值，归一化0.1-10.0
float cmp_f(int a, int b)
{
	float f1 = max2(to_float(a), 0.01);
	float f2 = max2(to_float(b), 0.01);
	//trace("a:" + a + " b:" + b + " f1:" + f1 + " f2:" + f2 + " f1/f2:" + (f1/f2));
	return min2(max2(f1/f2, 0.1), 10.0);
}

//比较敌我
int cmp_parm(object me, object target, mapping parm)
{
	float product = 1;
	int weight = 0;

	if(parm["prop"]) {				//属性
		foreach(string id, int w in parm["prop"]) {
			product *= pow(cmp_f(me->query(id), target->query(id)), w);
			weight += max2(w, 0);
		}
	}
	if(parm["temp"]) {				//临时属性
		foreach(string id, int w in parm["temp"]) {
			product *= pow(cmp_f(me->query_temp(id), target->query_temp(id)), w);
			weight += max2(w, 0);
		}
	}
	if(parm["attr"]) {
	}
	if(parm["skill"]) {				//有效技能等级
		foreach(string id, int w in parm["skill"]) {
			product *= pow(cmp_f(me->query_skill(id), target->query_skill(id)), w);
			weight += max2(w, 0);
		}
	}
	if(parm["skill_pair"]) {		//对应skill有效等级
		foreach(string* arr, int w in parm["skill_pair"]) {
			product *= pow(cmp_f(me->query_skill(arr[0]), target->query_skill(arr[1])), w);
			weight += max2(w, 0);
		}
	}
	if(parm["skill1"]) {			//原始技能等级
		foreach(string id, int w in parm["skill1"]) {
			product *= pow(cmp_f(me->query_skill(id, 1), target->query_skill(id, 1)), w);
			weight += max2(w, 0);
		}
	}
	if(parm["pair"]) {				//数据对
		foreach(int* arr, int w in parm["pair"]) {
			product *= pow(cmp_f(arr[0], arr[1]), w);
			weight += max2(w, 0);
		}
	}
	product = pow(product, 1.0 / weight) * 100 + 1;
	trace("cmp:" + getuid(me) + "/" + getuid(target) + " = " + product);
	return min2(to_int(product), 10000);
}

//比较敌我，之后取随机值(单位%)
int random_cmp(object me, object target, mapping parm)
{
	return random(cmp_parm(me, target, parm));
}

//比较敌我，加入20%的随机因素
int cmp_random20(object me, object target, mapping parm)
{	
	int n = cmp_parm(me, target, parm);
	n = MATH->random_pct(n, 20);
	return n;
}

//砍人
void fight_enemy(object who, object enemy)
{
	if(userp(who)) who->fight_ob(enemy);
	else if(!who->is_killing(enemy->query("id"))) who->kill_ob(enemy);
}

//搜索周围的room
void find_room(mapping rooms, object start, int depth)
{
	mapping exits = start->query("exits");
	rooms[start] = 1;
	if(depth && mapp(exits)) {
		foreach(mixed v in values(exits)) {
			object r = objectp(v) ? v : load_object(v);
			if(r && !rooms[r]) {
				find_room(rooms, r, depth - 1);
			}
		}
	}
}

//打断busy
void stop_busy(object who)
{
	if(who->is_busy()) {
		who->start_busy(1, 100);
		who->interrupt_me(0, 0);
	}
}

//kill
private void kill2(object who, object victim)
{
	if(!who->is_fighting(victim)) who->kill_ob(victim);
}

//复制敌人
void copy_enemy(object src, object dst)
{
	foreach(object enemy in enemies(src)) {
		if(enemy && living(enemy) && enemy != dst) {
			kill2(dst, enemy);
			if(userp(enemy))
				enemy->fight_ob(dst);
			else {
				kill2(enemy, src);
				kill2(enemy, dst);
			}
		}
	}
}

//保护某人
void protect(object me, object who)
{
	who->set_temp("protected", 1);
	who->set_temp("protect_ob", me->query("id"));
	me->set_temp("protect", who->query("id"));
	me->set_temp("protect_time", time());
}

//目标处于安全区
int in_safy(object who)
{
	object env = environment(who);
	return env && (env->query("no_fight") || env->query("no_magic"));
}

//忠实成员
int loyal_member(object who, string family)
{
	return who->query("family/family_name") == family
		&& !who->query("betray/count");
}

///开始busy
int start_no_move(object me, int duration)
{
	if(!me->query_temp("no_move")) {
		me->set_temp("no_move", 1);
		call_out("remove_no_move", duration, me);
		return 1;
	}
	return 0;
}

//移除no_move
void remove_no_move(object me) 
{
	if(me) me->delete_temp("no_move");
}
