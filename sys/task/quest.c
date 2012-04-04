// by firefox 04/10/2010
// ��������

#include <xyj_x.h>
#include <ansi.h>

inherit TT_GROUP;

void create()
{
	push_backs( ({"food", "ask", "kill", "armor", "weapon", "cloth", "give"}) );

	init_prop();
}

/********************************��ɫ����***********************************/

//������Ĳ�������
mapping color_data(object who)
{
	return DB->query_map(who, _stat_prop + "/colors");
}

//��ѯ��ɫ
int color_num(object who)
{
	mapping m = color_data(who);
	int n = 0;

	foreach(string k, int v in m) {
		if(v > 0) n++;
	}
	return n;
}

//����ȡ������һɫ
int color_remove(object who)
{
	mapping m = color_data(who);
	string* arr = ({});

	foreach(string k, int v in m) {
		if(v > 0) arr += ({k});
	}
	if(sizeof(arr)) m[random1(arr)] = 0;
}

//�������ĵ���ɫ
void color_consume(object who)
{
	mapping m = color_data(who);

	foreach(string k, int v in m) {
		if(v > 0) m[k]--;
	}
}

mapping _color_code = ([
	"food"			: HIR"��",
	"ask"			: HIG"��",
	"kill"			: HIY"��",
	"weapon"		: HIB"��",
	"armor"			: HIM"��",
	"give"			: HIC"��",
	"cloth"			: HIW"��",
]);

void show_clouds(object who)
{
	mapping m = color_data(who);

	string colors = "";
	int i = 0;

	foreach(string k, int v in m) {
		if(v > 0) {
			colors += _color_code[k];
			i++;
		}
	}
	colors += NOR;

    if(i < 1) return;

	if(i == 1)
		colors += "ɫ";
	else if(i == 2)
		colors += "��ɫ";
	else
		colors += chinese_number(i) + "��";

	tell_object(who, "�����������Ʈ����һС��" + colors + "���ơ�\n");
}

/********************************��������***********************************/

//ȡ��ȫ������
void cancel_all(object who)
{
	mapping m = data_of(who);
	if(!sizeof(m)) return;
	set_data(who, ([]));
	color_remove(who);
}

/********************************�һ�����***********************************/

string* _gifts = ({
	"strength", "courage", "intelligence", "spirituality", 
	"composure", "personality", "constitution", "karma"
});

//�����츳
string reward_gift(object who, int point)
{
	string gift = random1(_gifts);
	point = 2;

	add_gain(who, "gifts/" + gift, point);
	who->add_temp("apply/" + gift, point);

	return chinese_number(point) + "��" + e2c(gift);
}

private void _improve(object who, string name, int point, int level)
{	
	while(1) {
		int pot = level*level*2;
		if(point <= pot) break;
		who->improve_skill(name, pot, (level > 50));
		level++;
		point -= pot;
	}
	who->improve_skill(name, point, (level > 50));
}

//��������
string reward_skill(object who, int point)
{
	mapping skills = who->query_skills();
	string skill = sizeof(skills) ? random1(keys(skills)) : "force";
	int level = (skills ? skills[skill] : 0) + 1;

	point = point / 4 * 20;	//�����qn������40 intѧϰ

	_improve(who, skill, point, level);
	add_gain(who, "skills/" + skill, point);

	return chinese_number(point) + "��" + to_chinese(skill);
}

//����Ǳ��
string reward_pot(object who, int point)
{
	point /= 4;
	who->add("potential", point);	
	add_gain(who, "potential", point);

	return chinese_number(point) + "��Ǳ��";
}

//��������
string reward_dx(object who, int point)
{
	who->add("daoxing", point);
	add_gain(who, "daoxing", point);

	return COMBAT_D->chinese_daoxing(point) + "����";
}

//��������
string reward_silver(object who, int point)
{
	who->add("balance", point * 100);
	add_gain(who, "silver", point);
	return chinese_number(point) + "������";
}

/********************************�ʹ��ҽ�***********************************/

//ѡ��������
mapping _funs = ([
	"��ʿ��"		: (: reward_gift :),
	"������"		: (: reward_silver :),
	"�����"		: (: reward_skill :),
	"��־��"		: (: reward_pot :),
	"��ï��"		: (: reward_dx :),
]);

//���ֽ���
void pay(object me, object who)
{
	int balance = who->query(_stat_prop + "/balance");
	if(balance > 0) {
		//����ɫ�������㽱��ϵ��
		int color = color_num(who);
		int* tab = ({1, 2, 4, 6, 10, 11, 12, 15});		//�߶˽�����������
		int reward = tab[color];
		string color_str = color > 2 ? (chinese_number(color) + "��") : "";

		mapping m1 = ([ "��ʿ��" : 1, "������" : 2, "�����" : 3, "��־��" : 47, "��ï��" : 47]);
		string dachen = roulette(m1);

		//���㽱��
		if(total_exp(who) < 40*K) reward = max2(reward, 10);
		reward = reward * balance / 10;
		who->set(_stat_prop + "/balance", 0);

		msv("\nһ����$N����ӿ�𵭵���" + color_str + "���ơ�\n", who);
		msvx("$N��$n���͵���$r�������ƣ������������޹�Ȼ�����������㣡\n\n", me, who);
		msv("$n����ǰ���Ͻ���$N�ĵ�ǰ������¡�\n", me, who);

		who->start_busy (3, 3);
		call_out("reward_player", 2, me, who, reward, dachen);
	}
}

void reward_player(object me, object who, int reward, string dachen)
{
	string gain = evaluate(_funs[dachen], who, reward);
	color_consume(who);

	msvx("\n�Ա�������%s������$N˵�˼��䣬$N���˵�ͷ��\n", me, 0, dachen);
	msvx("%s��$Nһ�ݣ�������ּ����$R%s��\n\n", who, 0, dachen, gain);
	msv("$N��æ����һ�ݣ�С�������վ������\n", who);

	MONITOR_D->report_system_object_msg (who, "�õ�" + gain);
	who->interrupt_me();
}

