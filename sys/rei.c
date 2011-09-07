// by firefox 06/21/2010

#include <xyj_x.h>
#include <ansi.h>

/*
	ת��Ͷ̥

	- Ͷ̥Ҫȡ������/���/��������������б�
*/

#define REI_PROP		XYJ_X"/rei"		//ת������
#define	MIN_EXP			(3*M)			//Ͷ̥exp����
#define	MIN_MANA		3000			//Ͷ̥����/�������ޣ������������skill

string* _bak_prop = ({	//��Ҫ���ݵ�ǰ������
	"mud_age",
	"combat_exp",	"daoxing",	"potential",
});

string* _del_prop = ({	//��Ҫɾ����ǰ������

	"death",			//������ʧ
	"family",
	"betray",			//��ʦ��¼

	"force",	"max_force",	"maximum_force",	"force_factor",
	"mana",		"max_mana",		"maximum_mana",		"mana_factor",

	"bellicosity",
	"learned_points",

	"life",				//����&����
	"rsg_eaten",
	
	"spell_qiankun_on",
});

void create()
{
	seteuid(getuid());
}

//��ȡת����Ϣ����
mixed* query(object who)
{
	return DB->query_array(who, REI_PROP);
}

//����ת������exp
private int exp_sum(object who)
{
	int sum = 0;
	mapping* arr = query(who);
	foreach(mapping m in arr) {
		sum += m[CEXP] + m[DEXP] + m[PEXP]*4;
	}
	return sum;
}

//ת��������������С�ڹ涨ֵ������ת����exp��ֵ��С�ڹ涨ֵ
int precondition(object who)
{
	int n = sizeof(query(who)) + 1;
	int mana = who->query("max_mana") + who->query("max_force");
	int sum = exp_sum(who);
	sum += total_exp(who) + who->query(PEXP)*4;

	return mana/2 >= MIN_MANA
		&& sum/3/n >= MIN_EXP;
}

//�г�ת������
void list(object who)
{
	mapping* arr = query(who);
	write("ת��������\n");
	for(int i = 0; i < sizeof(arr); ++i) {
		printf("%2d:   %s\n", i, or2(arr[i]["name"], "����"));
	}
}

//���ݲ���λ����
private void reset_prop(object who)
{
	//���ݹؼ�����
	mapping bak = ([]);
	foreach(string prop in _bak_prop) {
		bak[prop] = who->query(prop);
		who->delete(prop);
	}
	bak["family"] = who->query("family/family_name");
	//ɾ����Ҫ���������
	foreach(string prop in _del_prop) {
		who->delete(prop);
	}
	//���skill
	SKI->clear_all(who);
	//��������
	bak["race"] = ([
		"id"	: RACE_D->query(who, "id"),
		"name"	: RACE_D->query(who, "name"),
	]);
	who->add(REI_PROP, ({ bak }) );
}

//�������
void to_earth(object who)
{
	tell_object(who, "�㽥��ʧȥ��֪����\n\n");
	tell_object(who, CYN"��֪��ȥ�˶���ʱ��...\n\n"NOR);

	who->set_temp("block_msg/all", 1);
	who->move("/obj/empty");

	call_out("go_home", 20, who);
}

//�յ�վ����
private void go_home(object who)
{
	object_f race;
	reset_prop(who);
	race = RACE_D->set_random(who);
	race->born(who);
}

