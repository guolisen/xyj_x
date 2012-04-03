// firefox 03/01/2012

#include <xyj_x.h>
#include <ansi.h>

inherit F_CLEAN_UP;

//��ѯ�츳
int query_attr(string prop, object who)
{
	if(prop == "int") return who->query_int();
	if(prop == "spi") return who->query_spi();
	return 0;
}
//��ѯ�����Ա���
int query_ratio(string prop0, string prop1, object who)
{
	int i0 = who->query(prop0);
	int i1 = who->query(prop1);
	if(intp(i0) && intp(i1) && i1 != 0) return 100 * i0 / i1;
	return 0;
}
//��ѯ������֮��
int query_diff(string prop0, string prop1, object who)
{
	int i0 = who->query(prop0);
	int i1 = who->query(prop1);
	if(intp(i0) && intp(i1)) return i0 - i1;
	return 0;
}
//������Ʒ����
int inv_count(object who, string id)
{
	int s = 0;
	foreach(object ob in all_inventory(who)) {
		if(ob->query("id") == id) {
			int n = ob->query_amount();
			s += n ? n : 1;
		}
	}
	return s;
}
//��������
mixed room_prop(object who, string prop)
{
	object room = environment(who);
	string* props = ({"short", "outdoors", "no_fight", "no_magic", "water"});

	if(member_array(prop, props) != -1) 
		return room->query(prop);
	if(prop == "exits") {
		mixed exits = room->query(prop);
		if(mapp(exits)) return implode(keys(exits), "|");
	}
	return 0;
}
//��������
string here_obj(object who, string id)
{
	object room = environment(who);
	object ob = id ? present(id, room) : 0;
	return ob ? ob->name() : 0;
}
//��ѯ����
string skill(object who, string skill)
{
	mapping m = who->query_learned();
	return who->query_skill(skill, 1) + "|" +
		and2(m, m[skill]) + "|" + 
		who->query_skill_mapped(skill);
}

//��ѯ����
string task(object who, string id)
{
	mapping m =  who->query(TASK_PROP"/list/" + id);
	if(!m) return "0|0|0|0|0|0";

	return m["ename"] + "|" + m["tname"] + "|" + m["tid"] + "|" +
		m["state"] + "|" + m["level"] + "|" 
		+ (m["remark"] != "" ? m["remark"] : "0");
}

//���Զ�Ӧ��
mapping _props = ([

	//hp
	"kee"			: "kee",
	"sen"			: "sen",		
	"eff_kee"		: "eff_kee",
	"eff_sen"		: "eff_sen",
	"kee_ratio"		: (: query_ratio, "eff_kee", "max_kee" :),
	"sen_ratio"		: (: query_ratio, "eff_sen", "max_sen" :),
	
	"force"			: "force",
	"mana"			: "mana",
	"max_force"		: "max_force",
	"max_mana"		: "max_mana",
	"force_ratio"	: (: query_ratio, "max_force", "maximum_force" :),
	"mana_ratio"	: (: query_ratio, "max_mana", "maximum_mana" :),

	"food"			: "food",
	"water"			: "water",
	"bellicosity"	: "bellicosity",

	"combat_exp"	: "combat_exp",
	"daoxing"		: "daoxing",

	"potential"		: (: query_diff, "potential", "learned_points" :),

	//score
	"title"			: "title",
	"name"			: "name",
	"id"			: "id",
	"age"			: "age",
	"int"			: (: query_attr, "int" :),
	"spi"			: (: query_attr, "spi" :),
	"damage"		: "damage",
	"armor"			: "armor",
	"family"		: "family/family_name",
	"master"		: "family/master_name",
	"balance"		: "balance",

	//i
	"count"			: (: inv_count :),

	//look
	"room"			: (: room_prop :),
	"here"			: (: here_obj :),

	//skills	
	"skill"			: (: skill :),

	//tasks	
	"task_norm"		: TASK_PROP"/norm",
	"task"			: (: task :),

	"stl_zg"		: (: query_diff, "sys_alx/exp", "sys_alx/exp_used" :),
]);


int main(object me, string arg)
{
	string title = "����ֵ";
	mixed result = 0;
	string* arr;
		
	if(!arg) return notify_fail("ָ���ʽ �� query [����:]<����>|<�����б�>\n");
	sscanf(arg, "%s:%s", title, arg);

	arr = explode(arg, ",");
	
	write("\n" + title + ":");
	foreach(string str in arr) {
		string fun, args;
		
		result = 0;
		if(sscanf(str, "%s(%s)", fun, args) == 2) {
			function f = _props[fun];
			if(functionp(f)) result = evaluate(f, me, args);
		} else {
			mixed v = _props[str];
			if(functionp(v)) result = evaluate(v, me);
			if(stringp(v)) result = me->query(v);
		}
		write(result + ",");
	}
	write("\n");

	return 1;
}

int help(object me)
{
	write(@HELP

ָ���ʽ �� query [����:]<����>|<�����б�>

��ѯ����/����������/�����б�(�Զ��ŷָ�)����ʾ����ѯ���Ե�ֵ����ָ��ּ�ڼ��ٴ���
ռ�ã�˼��Դ�Ա��������С�

hp���
- ��Ѫ/����kee sen eff_kee eff_sen kee_ratio sen_ratio 
- ����/������force mana max_force max_mana force_ratio mana_ratio
- ��ʳ/ɱ����water food bellicosity
- ����/Ǳ�ܣ�combat_exp daoxing potential

score���
- ����/ͷ�Σ�title name id
- ����/������damage armor
- ����/ʦ�У�family master
- ����/���ԣ�int spi
- ������     balance age

i���
- ��Ʒ������count(��ƷID)���������ϸ���Ʒ����

look���
- �������ԣ�room(����)�����ԣ�short exits outdoors no_fight no_magic water
- Ŀ����ڣ�here(Ŀ��ID)���鿴��Ŀ�������

skills���
- ������Ϣ��skill(����ID)

tasks���
- �����ȣ�task_norm
- ������Ϣ��task(����)
�����ʽΪ��<�������>/<����>�������������£�
- ����(mieyao)��mieyao
- ����(quest)��food weapon armor cloth ask give kill
- ����(forces)��cien
���������Ϊ��mieyao/mieyao����˽�����Ϊ��quest/food��

����
* ʨ����ս����stl_zg���������ָ������ߣ��ò�������ȥ

�÷�����
- ��Ѫ������query ��Ѫ:kee,eff_kee,kee_ratio
- �鿴���ܣ�query ����:skill(force),skill(spells)
- ������Ϣ��query task(mieyao/mieyao),task(quest/food)
- ������ͷ��query count(huangliang zhen)
- ������ڣ�query room(exits)
- NPC�ڷ�query here(li jing)

HELP
	);
	return 1;
}
