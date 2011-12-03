// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

#define BUSY					1
#define NO_MOVE					1
#define FIGHTING				1
#define DOTING					1


//��鼼��ǰ������
int require(object target, string name, mapping req)
{
	if(req["ex_temp"]) {	//��黥�⼼�ܵ���ʱ���
		foreach(string k, mixed v in req["ex_temp"]) {
			if(target->query_temp(k)) {
				if(stringp(v)) {
					printf(v + "\n");
				} else {
					printf("�㻹����ʩ��" + name + "��\n");
				}
				return 0;
			}
		}
	}
	if(req["ex_value"]) {	//��黥�⼼�ܵı��
		foreach(string k, mixed v in req["ex_value"]) {
			if(target->query(k)) {
				if(stringp(v)) printf(v + "\n");
				else printf("�㻹����ʩ��" + name + "��\n");
				return 0;
			}
		}
	}
	if(req["ex_class"]) {	//���ĳ�໥��buff
		foreach(string k, mixed v in req["ex_class"]) {
			if(BUFF->find2(target, k)) {
				if(stringp(v)) printf(v + "\n");
				else printf("Ŀ�����Ѿ�����" + k + "��\n");
				return 0;
			}
		}
	}
	if(req["skill"]) {		//���skillҪ��
		foreach(string k, int v in req["skill"]) {
			int lvl = target->query_skill(k);
			if(lvl < v) {
				printf("�����Ϊ������ʩ��" + name + "��\n");
				return 0;
			}
		}
	}
	if(req["skill1"]) {		//���skillҪ��
		foreach(string k, int v in req["skill1"]) {
			int lvl = target->query_skill(k, 1);
			if(lvl < v) {
				printf("�����Ϊ������ʩ��" + name + "��\n");
				return 0;
			}
		}
	}
	if(req["skill_map"]) {	//���skill map
		foreach(string k, int v in req["skill_map"]) {			
			if(target->query_skill_mapped(k) != v) {
				printf("����뼤��" + to_chinese(v) + "����ʩ��" + name + "��\n");	//TODO:����
				return 0;
			}
		}
	}
	if(req["prop"]) {		//���״̬��ֵ
		foreach(string k, int v in req["prop"]) {
			int n = target->query(k);
			if(n < v) {
				printf("��״̬���ѣ�����ʩ��" + name + "��\n");
				return 0;
			}
		}
	}
	if(req["cd"]) {			//��鼼����ȴ
		foreach(string k, int v in req["cd"]) {
			if(BUFF->query_cd(target, k)) {
				printf("����Ҫ��һ��ʱ�����ʩ��" + name + "��\n");
				return 0;
			}
		}
	}
	return 1;
}

//��鲻��״̬
string bad_state(object target, string* status)
{
	foreach(string s in status) {
		if(s == "busy" && (target->is_busy() 
			|| target->query_temp("pending/exercising"))) {
			return "������æ����";
		}
		else if(s == "fighting" && target->is_fighting()) {
			return "���ڴ�ܣ���Ͼ����";
		}
		else if(s == "no_move" && target->query_temp("no_move")) {
			return "�޷��ƶ�";
		}
		else if(s == "ghost" && target->is_ghost()) {
			return "�ǹ��";
		}
		else if(s == "invisible" && target->query("env/invisibility")) {
			return "��������";
		}
	}
	return 0;
}

//��ȡĿ����ٻ���
object invoker(object who)
{
	object inv;		
	while(who && inv = who->query_temp("invoker")) who = inv;	//�༶�ٻ�
	return who;
}

//ȫ������
object* enemies(object me)
{
	me->clean_up_enemy();
	return me->query_enemy();
}

//���ѡ�����
object random_enemy(object me)
{
	object* arr = enemies(me);
	return sizeof(arr) ? random1(arr) : 0;
}

//�Ƿ�ɹ���Ŀ��
int can_attack(object me, object target)
{
	if(!target
		|| !target->is_character()
		|| target->is_corpse()
		|| target == me)
		return 0;
	return 1;
}

//���Ŀ���Ƿ���������
int check_target(object me, object target, mapping m)
{
	object env = environment(target);

	if(m["need_target"] && !target) return notify_fail("����ָ��һ��Ŀ�ꡣ\n");
	if(m["need_enemy"] && (!target || !me->is_fighting(target)))
		return notify_fail("����ָ��һ���ж�Ŀ�ꡣ\n");
	if(m["need_enemies"] && !sizeof(enemies(me)))
		return notify_fail("û�еж�Ŀ�ꡣ\n");
	if(m["need_kill"] && !target->is_killing(me))
		return notify_fail("�Է����㲢������ޡ�\n");
	if(m["need_living"] && !living(target))
		return notify_fail("����ָ��һ��������Ŀ�ꡣ\n");
	if(m["need_no_busy"] && target->is_busy())
		return notify_fail("Ŀ���Թ˲�Ͼ�����ض��һ�١�\n");
	if(m["can_move"] && is_no_move(target))
		return notify_fail("Ŀ���޷��ƶ������ض��һ�١�\n");
	if(m["can_fight"] && !(env->query("no_fight") || env->query("no_magic")))
		return notify_fail("Ŀ�괦�ڰ�ȫ����\n");
	return 1;
}

//��ȡ�ɹ���Ŀ�꣬�����target�������ѡ��
object get_victim(object me, object target)
{
	if(!target) target = random_enemy(me);
	if(!can_attack(me, target))	return 0;
	return target;
}

//֧�����ܳɱ�
void pay(object target , mapping cost)
{
	foreach(string k, int v in cost) {
		target->add(k, -v);
	}
}

//��ȡ�����츳
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
	else if(attr == "dodge") {					//�Ṧ
		return target->query_skill("dodge");
	}
	else if(attr == "attack") {					//��������
		object weapon = target->query_temp("weapon");
		string skill = weapon ? weapon->query("skill_type") : "unarmed";
		return target->query_skill(skill);
	}
	return 0;
}

//a��b�ı�ֵ����һ��0.1-10.0
float cmp_f(int a, int b)
{
	float f1 = max2(to_float(a), 0.01);
	float f2 = max2(to_float(b), 0.01);
	//trace("a:" + a + " b:" + b + " f1:" + f1 + " f2:" + f2 + " f1/f2:" + (f1/f2));
	return min2(max2(f1/f2, 0.1), 10.0);
}

//�Ƚϵ���
int cmp_parm(object me, object target, mapping parm)
{
	float product = 1;
	int weight = 0;

	if(parm["prop"]) {				//����
		foreach(string id, int w in parm["prop"]) {
			product *= pow(cmp_f(me->query(id), target->query(id)), w);
			weight += max2(w, 0);
		}
	}
	if(parm["temp"]) {				//��ʱ����
		foreach(string id, int w in parm["temp"]) {
			product *= pow(cmp_f(me->query_temp(id), target->query_temp(id)), w);
			weight += max2(w, 0);
		}
	}
	if(parm["attr"]) {
	}
	if(parm["skill"]) {				//��Ч���ܵȼ�
		foreach(string id, int w in parm["skill"]) {
			product *= pow(cmp_f(me->query_skill(id), target->query_skill(id)), w);
			weight += max2(w, 0);
		}
	}
	if(parm["skill_pair"]) {		//��Ӧskill��Ч�ȼ�
		foreach(string* arr, int w in parm["skill_pair"]) {
			product *= pow(cmp_f(me->query_skill(arr[0]), target->query_skill(arr[1])), w);
			weight += max2(w, 0);
		}
	}
	if(parm["skill1"]) {			//ԭʼ���ܵȼ�
		foreach(string id, int w in parm["skill1"]) {
			product *= pow(cmp_f(me->query_skill(id, 1), target->query_skill(id, 1)), w);
			weight += max2(w, 0);
		}
	}
	if(parm["pair"]) {				//���ݶ�
		foreach(int* arr, int w in parm["pair"]) {
			product *= pow(cmp_f(arr[0], arr[1]), w);
			weight += max2(w, 0);
		}
	}
	product = pow(product, 1.0 / weight) * 100 + 1;
	trace("cmp:" + getuid(me) + "/" + getuid(target) + " = " + product);
	return min2(to_int(product), 10000);
}

//�Ƚϵ��ң�֮��ȡ���ֵ(��λ%)
int random_cmp(object me, object target, mapping parm)
{
	return random(cmp_parm(me, target, parm));
}

//�Ƚϵ��ң�����20%���������
int cmp_random20(object me, object target, mapping parm)
{	
	int n = cmp_parm(me, target, parm);
	n = MATH->random_pct(n, 20);
	return n;
}

//����
void fight_enemy(object who, object enemy)
{
	if(userp(who)) who->fight_ob(enemy);
	else if(!who->is_killing(enemy->query("id"))) who->kill_ob(enemy);
}

//������Χ��room
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

//���busy
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

//���Ƶ���
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

//����ĳ��
void protect(object me, object who)
{
	who->set_temp("protected", 1);
	who->set_temp("protect_ob", me->query("id"));
	me->set_temp("protect", who->query("id"));
	me->set_temp("protect_time", time());
}

//Ŀ�괦�ڰ�ȫ��
int in_safy(object who)
{
	object env = environment(who);
	return env && (env->query("no_fight") || env->query("no_magic"));
}

//��ʵ��Ա
int loyal_member(object who, string family)
{
	return who->query("family/family_name") == family
		&& !who->query("betray/count");
}

///��ʼbusy
int start_no_move(object me, int duration)
{
	if(!me->query_temp("no_move")) {
		me->set_temp("no_move", 1);
		call_out("remove_no_move", duration, me);
		return 1;
	}
	return 0;
}

//�Ƴ�no_move
void remove_no_move(object me) 
{
	if(me) me->delete_temp("no_move");
}
