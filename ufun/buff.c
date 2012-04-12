// by firefox 11/21/2009
// buff������Ŀ�����������dbase

#include <xyj_x.h>
#include <ansi.h>

inherit F_NO_CLEAN_UP;

#define PROP			"buff"
#define ID(id)			(PROP"/" + id)

//buff������id
string id(string id1)
{
	return ID(id1);
}

//��Ŀ���ϲ���ָ��id��buff
mixed find(object me, string id)
{
	return me->query_temp(ID(id));
}

//��Ŀ���ϲ���ָ������buff
mapping find2(object me, string class_name)
{
	mixed buffs = me->query_temp(PROP);
	if(!mapp(buffs)) return 0;

	foreach(string id, mapping buff in buffs) {
		if(buff["class"] == class_name) return buff;
	}
	return 0;
}

//ΪĿ��buff
mapping add(object me, mapping buff)
{
	string id = ID(buff["id"]);
	if(!me) return 0;
	if(me->query_temp(id)) {
		if(buff["done_msg"]) printf(buff["done_msg"]);
		return 0;
	}
	me->set_temp(id, buff);
	buff["me"] = me;

	if(buff["temp"]) {		//������ʱ��־
		foreach(string k, mixed v in buff["temp"]) {
			me->set_temp(k, v);
		}
	}
	if(buff["add_temp"]) {	//�ۼ���ʱ��־
		foreach(string k, int v in buff["add_temp"]) {
			me->add_temp(k, v);
		}
	}
	if(buff["add_apply"]) {		//����apply
		foreach(string k, int v in buff["add_apply"]) {
			me->add_temp("apply/" + k, v);
		}
	}
	if(buff["replace"]) {	//�滻״̬
		mapping m = ([]);
		foreach(string k, mixed v in buff["replace"]) {
			m[k] = me->query(k);
			me->set(k, v);
		}
		if(!me->query(id)) me->set(id, m);	//����ԭʼ״̬
	}
	if(buff["add"]) {		//״̬����ֵ����������
		foreach(string k, mixed v in buff["add"]) {
			me->add(k, v);
		}
	}
	if(buff["interval"] && buff["timer_act"]) {	//���ڴ�������Ϊ������0��buff���Ƴ���
		call_out("on_timer", buff["interval"] * SEC_PER_HB, buff);
	}
	if(buff["duration"] > 0) {	//��ԭ
		call_out("remove1", buff["duration"] * SEC_PER_HB, buff);
	}
	if(buff["start_msg"]) msv(buff["start_msg"] + "\n"NOR, me);
	return buff;
}

//buff�Ƿ���Ч������Ŀ��֮��
int valid(mapping buff)
{
	object me;
	if(!mapp(buff) || !(me = buff["me"])) return 0;
	return buff == find(me, buff["id"]);
}

varargs void remove1(mapping buff, int silent);

//���ڴ���buff����Ϊ
void on_timer(mapping buff)
{
	if(!valid(buff)) return;

	if(evaluate(buff["timer_act"], buff)) {
		call_out("on_timer", buff["interval"] * SEC_PER_HB, buff);
	} else {
		remove1(buff);
	}
}

//�Ƴ����滻��״̬
private void reset_replace(object me, string id)
{
	mapping m = me->query(id);
	foreach(string k, mixed v in m) {
		me->set(k, v);
	}
	me->delete(id);
}

//��ȥ��ʱ����(��������)
void sub_temp(object me, string prop, mixed value)
{
	if(arrayp(value)) {
		mixed* arr = me->query_temp(prop);		//for temp array
		trace(sizeof(arr));
		arr -= value;
		trace(sizeof(arr));
		me->set_temp(prop, arr);
	}			
	else me->add_temp(prop, -value);
}

//��Ŀ���ϵ��Ƴ�buff
varargs void remove1(mapping buff, int silent)
{
	object me;
	string id;
	if(!valid(buff) || buff["removed"]) return;	//��ֹ�ݹ��ظ�ɾ��
	buff["removed"] = 1;

	me = buff["me"];
	id = ID(buff["id"]);

	if(buff["temp"]) {
		foreach(string k, mixed v in buff["temp"]) {
			me->delete_temp(k);
		}
	}
	if(buff["add_temp"]) {
		foreach(string k, mixed v in buff["add_temp"]) {
			sub_temp(me, k, v);
		}
	}
	if(buff["add_apply"]) {
		foreach(string k, int v in buff["add_apply"]) {
			me->add_temp("apply/" + k, -v);
		}
	}
	if(buff["replace"]) {
		reset_replace(me, id);
	}
	if(buff["add"]) {
		foreach(string k, mixed v in buff["add"]) {
			me->add(k, -v);
		}
	}
	if(buff["object"]) {	//���ٺ�buff������صĶ���
		foreach(string k, object v in buff["object"]) {
			if(v) destruct(v);
		}
	}
	if(buff["link"]) {
		foreach(mapping k, mixed v in buff["link"]) {
			remove1(k, silent);
		}
		buff["link"] = 0;	//��ֹѭ������Ӱ��GC
	}
	if(buff["post_act"]) evaluate(buff["post_act"], buff);

	if(objectp(me)) {	//me���ܱ�post_act����
		if(buff["stop_msg"]) msv(buff["stop_msg"] + "\n"NOR, me);
		me->delete_temp(id);
	}
}

//��Ŀ���ϵ��Ƴ�ָ��id��buff
void remove2(object me, string id)
{
	remove1(find(me, id));
}

//���Ŀ���ϵ�����״̬
void clear(object me)
{
	mixed buffs = me ? me->query_temp(PROP) : 0;
	if(!mapp(buffs)) return;
	foreach(string id in keys(buffs)) {
		remove2(me, id);
	}
}

//��������buff��ʹǰ�߱�ɾ��ʱͬʱɾ������
void link(mapping buff1, mapping buff2)
{
	if(!mapp(buff1["link"])) buff1["link"] = ([]);
	buff1["link"] += ([buff2 : 1]);
}

//������������buff
void link_each(mapping buff1, mapping buff2)
{
	link(buff1, buff2);
	link(buff2, buff1);
}

//�޸�δ����ȡ����buff
void repair(object me)
{
	mixed replace = me->query(PROP);
	if(!mapp(replace)) return;

	foreach(string id, mapping m in replace) {
		if(!find(me, id)) reset_replace(me, ID(id));
	}
}

//�޸�δ����ȡ����buff����AT_D����
void start()
{
	foreach(object user in users()) {
		repair(user);
		reset_eval_cost();
	}
}

//�г�Ŀ�����������е�buff
varargs int list(object me, int all)
{
	mixed buffs = me->query_temp(PROP);
	string name = me->name() ? me->name() : me->query("short");

	if(!mapp(buffs) || sizeof(buffs) == 0) {
		printf("%s��û���κ�״̬��\n\n", name);
	} else {
		printf("%s�ϵ�״̬��\n\n", name);
		foreach(string id, mapping buff in buffs) {
			if(all || !buff["attr"]) {
				string c = buff["class"] ? "(" + buff["class"] + ")" : "";
				string d = buff["duration"] > 0 ? "����" + buff["duration"] + "�롣" : "";
				printf("%-40s%s\n", buff["name"] + c, buff["comment"] + d);
			}
		}
	}
	printf("\n");
	return 1;
}

//��ʼ��ȴ
mapping start_cd(object me, string id, string name, int duration)
{
	mapping buff = ([
		"id"		: id + "_cd",
		"name"		: name + "��ȴ",
		"comment"	: name + "��ȴ���˼����" + name + "��",
		"duration"	: duration,
	]);	
	return add(me, buff);
}

//buff��ʼ��ȴ
mapping start_cd2(object me, mapping buff, int duration)
{
	return start_cd(me, buff["id"], buff["name"], duration);
}

//��ʼ��ʱ��
varargs mapping start_timer(object me, function f, string id, int interval, int duration)
{
	mapping buff = ([
		"id"		: "timer" + id,
		"name"		: "��ʱ��",
		"comment"	: "��ʱ����ʱִ��ĳ������",
		"duration"	: duration,
		"interval"	: or2(interval, 2),
		"timer_act"	: f,
	]);
	return add(me, buff);
}

//��ʼ��ֹʩ��
mapping start_no_cast(object me, int duration)
{
	mapping buff = ([
		"id"		: "no_cast",
		"name"		: "������ȴ",
		"comment"	: "������ȴ���˼䲻��ʩ���κη�����",
		"duration"	: duration,
		"add_temp"	: (["no_cast" : 1]),
	]);
	return add(me, buff);
}

//��ʼ��ֹ�ƶ�
mapping start_no_move(object me, int duration)
{
	mapping buff = ([
		"id"		: "no_move",
		"name"		: "��ֹ�ƶ�",
		"comment"	: "�ڼ䲻���ƶ���",
		"duration"	: duration,
		"add_temp"	: (["no_move" : 1]),
	]);
	return add(me, buff);
}

//��ʼ��ֹ�ƶ�
mapping start_no_attack(object me, int duration)
{
	mapping buff = ([
		"id"		: "no_attack",
		"name"		: "��ֹ����",
		"comment"	: "�ڼ䲻�ܹ�����",
		"duration"	: duration,
		"add_temp"	: (["no_attack" : 1]),
	]);
	return add(me, buff);
}

//��ʼ��״̬�������κο���
mapping start_frenzy(object me, int duration)
{
	mapping buff = ([
		"id"		: "frenzy",
		"name"		: HIR"��״̬"NOR,
		"comment"	: "�����κο��ơ�",
		"duration"	: duration,
		"interval"	: 1,
		"timer_act"	:  function(mapping buff) {
			object me = buff["me"];
			if(me->is_busy()) me->start_busy(1);
			if(me->query_temp("no_cast")) me->delete_temp("no_cast");
			return 1;
		},
	]);
	return add(me, buff);
}

//��ʼ��ֹ����
varargs mapping start_no_wield(object me, int duration, string msg)
{
	mapping buff = ([
		"id"		: "no_wield",
		"name"		: HIY"��������"NOR,
		"comment"	: "��ֹʹ��������",
		"duration"	: duration,
		"add_temp"	: ([ "No_Wield" : 1 ]),
		"stop_msg"	: msg,
		"post_act"	: function(mapping buff) {
			object weapon = buff["_weapon"];
			if(weapon && environment(weapon) == buff["me"]) {
				weapon->wield();
			}
		},
		"_weapon"	: me->query_temp("weapon"),

	]);
	object weapon;
	while(weapon = me->query_temp("weapon")) weapon->unequip();
	return add(me, buff);
}

//��ʼ����צ��
varargs mapping start_claw(object me, int duration, int damage, string msg)
{
	mapping buff = ([
		"id"		: "claw",
		"name"		: HIY"������צ"NOR,
		"comment"	: "������צ���˺����ӣ�������������",
		"duration"	: duration,
		"temp"		: ([ "no_wield"		: 1 ]),
		"add_temp"	: ([ "apply/damage"	: damage ]),
		"stop_msg"	: msg,
	]);
	object weapon;
	while(weapon = me->query_temp("weapon")) weapon->unequip();
	return add(me, buff);
}



//�����۶�(һ��ʱ��)������ʹ��
mapping start_broken(object weapon, int duration)
{
	mapping buff = ([
		"id"		: "broken",
		"name"		: "�۶�",
		"comment"	: "��������",
		"duration"	: duration,
		"replace"	: ([
			"name"		: "�۶ϵ�" + weapon->query("name"),
			"weapon_prop" : 0,
		]),
	]);
	return add(weapon, buff);
}

//��ʼ������������ʱ
varargs mapping start_life(object me, int duration, string msg)
{
	mapping buff = ([
		"id"		: "life_countdown",
		"name"		: HIY"��������ʱ"NOR,
		"comment"	: "Ŀ����������ʱ����ʱ����Ŀ�걻���١�",
		"duration"	: duration,
		"stop_msg"	: msg,
		"post_act"	: function(mapping buff) {
			msv(buff["stop_msg"] + "\n"NOR, buff["me"]);
			destruct(buff["me"]); 
		},
	]);
	return add(me, buff);
}


//����Ŀ����Ѫ/�����״̬
private varargs mapping start_add_hpx(object me, string prop, string name, int gain, int duration, string msg)
{
	string color = gain > 0 ? HIG : HIR;
	string title = (gain > 0 ? "����" : "����") + name;
	mapping buff = ([
		"id"		: "add_hp_" + prop,
		"name"		: color + title + NOR,
		"comment"	: "��ʱ" + title + "��",
		"duration"	: duration,
		"add"		: ([ "max_" + prop : gain, "eff_" + prop : gain, prop : gain ]),
		"stop_msg"	: msg,
		"_prop"		: prop,
		"_gain"		: gain,
		"post_act"	: function(mapping buff) {
			object me = buff["me"];			
			string prop = buff["_prop"];
			int gain = buff["_gain"];
			int max_hp = me->query("max_" + prop);
			//����״̬����ǰ��Ч״̬����
			int radio = (me->query("eff_" + prop) + gain) * 100	/ (max_hp + gain);
			int hp = max_hp * radio / 100;

			me->set(prop, hp);
			me->set("eff_" + prop, hp);			
		},
	]);
	return add(me, buff);
}

//����Ŀ����Ѫ
varargs mapping start_add_kee(object me, int gain, int duration, string msg)
{
	return start_add_hpx(me, "kee", "��Ѫ", gain, duration, msg);
}

//����Ŀ�꾫��
varargs mapping start_add_sen(object me, int gain, int duration, string msg)
{
	return start_add_hpx(me, "sen", "����", gain, duration, msg);
}

//��ʱ�޸���buff�е�replaceδ��������ԭ
mapping start_repair(object me, int interval)
{
	mapping buff = ([
		"id"		: "buff_repair",
		"name"		: HIG"��ʱ�޸�"NOR,
		"comment"	: "��ʱ�޸���buff�е�replaceδ��������ԭ��",
		"interval"	: interval,
		"timer_act"	: function(mapping buff) {
			foreach(object user in users()) {
				repair(user);
			}
			return 1;
		},
	]);
	return add(me, buff);
}

//��ȡ��ȴ��Ϣ
mixed query_cd(object me, string id)
{
	return me->query_temp(ID(id + "_cd"));
}

//��ȡbuff����ȴ��Ϣ
mixed query_cd2(object me, mapping buff)
{
	return query_cd(me, buff["id"]);
}

