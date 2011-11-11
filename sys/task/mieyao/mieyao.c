// by firefox 04/10/2010
// ��������

#include <xyj_x.h>

inherit TT_BASE;

#define APPLY_CD			60		//�����������ȴʱ�䣬��ֹ����Ҫ100������
#define PROP_GUAI			"mieyao_guai"

string* _list = ({
	"yg-putuo",		"yg-moon",		"yg-wzg",		"yg-fangcun",
	"yg-hell",		"yg-jjf",		"yg-dragon", 
	"yg-xueshan",	"yg-wdd",		//"yg-hyd",		"yg-psd",
});

void create()
{
	init_prop(2400);
	_show_id = 1;
}

/********************************��������***********************************/

//��ȡ��ҹֶ���
object query_guai(object who)
{
	return who->query_temp(PROP_GUAI);
}

/********************************��������***********************************/

//����skill
private string reward_skill(object who)
{
	mapping skills = who->query_skills();
	mixed* tab = ({
		({1,	0}),
		({70,	100}),
		({140,	50}),
		({210,	25}),
		({K*K,	17}),
	});
	int n = sizeof(skills);
	if(skills && n >= 1) {
		string id = random1(keys(skills));
		int level = skills[id];
		int p = MATH->cvt_rang(tab,	level);
		
		if(p > random(100) && n > random(10)) {					//firefox 2011.11
			string name = to_chinese(id);
			who->set_skill(id, level + 1);
			tell_object(who, "��õ���һ��" + name + "��\n");
			who->command_function("rumor ��˵" + who->query("name") + "��" + name + "�����������ˣ�");
			return id;
		}
	}
	return 0;
}

//���㽱��
private int calc_reward(object who, int level)
{
	int n1 = 800 * 2;
	int n2 = 2000 * 2;
	int m = 3000;

	int exp = min2(total_exp(who) / 2 / K, m);

	return (n1 + (n2 - n1) * exp / m) * (level + 1) / 10;
}

//�ֵǳ�
private string go_where(object guai)
{
	int exp = total_exp(guai) / 2 / K;
	int dirs = MATH->find_rang( ({ 200, 5*K, K*K }), exp );

	object room = PLACE->random_drop(guai, dirs);
	trace(base_name(room) + " exp:" + exp + " dir:" + dirs);

	return MISC_D->find_place(environment(guai));
}

/********************************�麯��ʵ��***********************************/

//��������ǰ������
int pre_check(object employer, object who)
{
	if(total_exp(who) > 100*K && employer->name() == "Ԭ���") {
		msvx("$N��$nһ���֣���λ$r����ȥ��͢Э��������\n", employer, who);
		return 0;
	}
	return 1;
}

//������
void new_task(object who, mapping task)
{
	object guai = new(__DIR__"npc/" + random1(_list));

	task["level"] = (task["level"] + 1) % 10;
	task["level"] = max2(task["level"], 1);

	guai->invocation(who, task["level"]);
	who->set_temp(PROP_GUAI, guai);

	//������ֵ
	task["tid"]		= guai->query("id");
	task["tname"]	= guai->query("name");
	task["sth"]		= go_where(guai);
	task["remark"]	= task["sth"];
	task["reward"]	= calc_reward(who, task["level"]);			//ȷ��������	
	task["cd"]		= time() + APPLY_CD;
}

//���轱��
void give_reward(object who, int reward)
{
	mapping m = data_of(who);
	int wx = reward / 2;
	int qn = reward / 2 / 4;
	
	who->add(CEXP, wx);
	who->add(PEXP, qn);
	parent()->add_gain(who, CEXP, wx);
	parent()->add_gain(who, PEXP, qn);

	tell_object(who, "��õ���" + chinese_number(wx)
		+ "����ѧ�����" + chinese_number(qn) + "��Ǳ�ܣ�\n");

	if(m["level"] == 9) reward_skill(who);
}

//���Ժ���
int debug(object employer, object who, string arg)
{
	object ob = query_guai(who);
	
	if(ob) {
		who->move(environment(ob));	
		who->set_leader(ob);	
	}
	tell_object(who, "\nOK.\n");
	return 1;
}

