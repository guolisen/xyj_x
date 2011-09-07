// by firefox 09/14/2010

#include <xyj_x.h>
#include <ansi.h>

inherit TT_Q4;
inherit TDB_SIMPLE;

#define MAX_CANPIAN				100		//�ִ��Ƭ���ﵽ��ֵ������Ϊ50%

#define REWARD1					10*K
#define REWARD10				100*K
#define GIFT					X_DIR"obj/gift/hua-puti"
#define BALANCE					(_stat_prop + "/cien/balance")

void create()
{
	init_param(REWARD1 * 3 / 2, REWARD1, 0, 0);
	tdb_load(X_DATA_DIR + "task/forces/_" + id());
}

//���ǰ������
int pre_check(object employer, object who)
{
	mapping msg = get_msg(employer);
	mapping m = data_of(who);

	if(m["state"] == "����") {
		msvx(msg["repeat"], employer, who, m["tname"]);
		return 0;
	}
	//���ֽ���
	if(who->query(BALANCE) > REWARD10 && total_exp(who) >= 5*K*K) {

		msv("$N��$n˵������æ��æ���������ۻ軨�����Ȱ�æ��ʶһ�¡�\n", employer, who);
		msv("$N�Ѿ��Ĳ�Ƭ�ݵ�$n��ǰ�������ּ��߲�����ϡ�ɼ���\n", employer, who);

		if(m["word"]) SCREEN->show(m["word"]);
		else m["word"] = SCREEN->random4c();
		
		return 0;
	}
	return 1;
}

//���ֽ���������������Ҫ�һ����Լ�����ɫ
void give_reward(object who, int reward)
{
	who->add(BALANCE, reward);
	who->add(FAME_PROP + "/misc/cien", REWARD1 / 2);
//	trace(BALANCE + ":" + reward);
}

//�ش����⣬���ֽ���
int answer(object employer, object who, string str)
{
	mapping m = data_of(who);
	
	if(!str || !m["word"]) return 0;

	msvx(CYN"$n�ش�$N����%s��\n"NOR,  employer, who, str);
	if(lower_case(m["word"]) == lower_case(str)) {
		object ob = new_to(GIFT, who);

		msv(CYN"\n$N��$n˵�����������޲��澭����������!\n"NOR, employer, who);
		if(ob) {			
			msvx(CYN"$N��$nһ��%s��\n"NOR, employer, who, ob->name());
			
			who->add(BALANCE, -REWARD10);
			parent()->add_gain(who, DEXP, REWARD10 / 5);
			parent()->add_gain(who, PEXP, REWARD10 * 4 / 5 / 4);
		}
	} else {
		msv("$Nҡͷ����ǰ�����岻ͨ���´��ٷ���ʩ���ɡ�\n", employer);
	}
	m["word"] = 0;
	
	return 1;

}

/********************************���Ժ���***********************************/
string _canpian = __DIR__"cien/canpian";

//�����Ƭ
void drop_sth(object env)
{	
	if(env) {
		int n = sizeof(children(_canpian));
		int i = sizeof(all_inventory(env));
		mapping exits = env->query("exits");
		for(int j = 0; j < 2; ++j) {
			if(random(n * 2) < MAX_CANPIAN && i < 30 && exits && sizeof(exits) > -1) {
				object ob = new(_canpian);
				if(!ob->move(env)) destruct(ob);
			}
		}
	}
}
/********************************���Ժ���***********************************/
//���Ժ���
int debug(object employer, object who, string arg)
{
	mapping m = data_of(who);
	object ob = new_to(_canpian, who);
	
	if(m["tname"]) ob->set_name(m["tname"], ({ m["tid"] }));

	tell_object(who, "\nOK.\n");
	return 1;
}

