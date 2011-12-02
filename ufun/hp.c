// by firefox 11/21/2009

#include <xyj_x.h>

//���ӷ���
void add_mana(object who, int value)
{
	int full = who->query("max_mana") * 2;
	who->add("mana", value);
	if(who->query("mana") > full) who->set("mana", full);
}

//��������
void add_force(object who, int value)
{
	int full = who->query("max_force") * 2;
	who->add("force", value);
	if(who->query("force") > full) who->set("force", full);
}

//ʹ���������/����
void en_max(object who)
{
	who->set("force_factor", who->query_skill("force")/2);
	who->set("mana_factor", who->query_skill("spells")/2);
}

//�ظ�Ŀ�����״̬
varargs void full(object who, int no_force)
{
	mapping db = who->query_entire_dbase();

	db["kee"]		= db["max_kee"];
	db["eff_kee"]	= db["max_kee"];
	db["sen"]		= db["max_sen"];
	db["eff_sen"]	= db["max_sen"];

	if(!no_force) {
		db["mana"]		= db["max_mana"] * 2;
		db["force"]		= db["max_force"] * 2;
		en_max(who);				
	}	
	who->clear_condition();
}

//��Ŀ�������ֵ���൱�ڼ���power��1/1000
int eval(object who)
{
	int exp = who->query(CEXP) + who->query(DEXP) / 2;	// + who->query(PEXP) * 4;
	exp = sqrt(1.0 * max2(exp, 1));
	return exp > 1 ? exp : 1;
}

//Ŀ�꼯�ϵ�����ֵ��ֵ
int eval_all(object* users)
{
	int s = 0;
	foreach(object ob in users) {
		s += eval(ob);
	}
	return s;
}

//����������״̬״̬
void mana_to_max(object who)
{
	int mana = SKI->basic_level(who, "spells") * 10;
	who->set("maximum_mana", mana);
	who->set("max_mana", mana);
}

//����������״̬״̬
void force_to_max(object who)
{
	int force = SKI->basic_level(who, "force") * 10;
	who->set("maximum_force", force);
	who->set("max_force", force);
}

//�ﵽ���״̬
int to_max(object who)
{
	mana_to_max(who);
	force_to_max(who);
	en_max(who);
	full(who);
}

//��������������
void copy_prop(object src, object dest, string* tab)
{
	foreach(string prop in tab) {
		dest->set(prop, src->query(prop));
	}
}

//��������������
void copy_skills(object src, object dest, int ratio)
{
	mapping skills = src->query_skills();
	mapping enables = src->query_skill_map();
	if(!skills) return;
	foreach(string skill, int lvl in skills) {
		dest->set_skill(skill, lvl * ratio / 100);
	}
	if(!enables) return;
	foreach(string k, string v in enables) {
		dest->map_skill(k, v);
	}
}

//������������Ҫ����
void copy_status(object src, object dest, int ratio)
{
	string* tab = ({CEXP, DEXP, "max_kee", "max_sen", "max_force", "max_mana"});

	copy_prop(src, dest, tab);
	copy_skills(src, dest, ratio);

	full(dest);
	en_max(dest);
}

int hp_test()
{
	return eval(find_player("firefox"));
}
