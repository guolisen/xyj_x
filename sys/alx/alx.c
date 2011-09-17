// by firefox 11/21/2009
// alxս��

#pragma optimize

inherit F_DBASE;

#include "camp.c"
#include "score.c"
#include "cmds.c"
#include "room_act.c"
#include "helper.c"

#include "alx.h"

/********************************˽�б���***********************************/

int _time;									//ս������ʱ��

/********************************��������***********************************/

int stop();

private void report(object obj, string msg);
private void chat(int camp, string str);

private int on_timer(mapping buff);

/********************************��ʼ��***********************************/

void create()
{
	seteuid(getuid());
	
	_status	= DONE;
	//BUFF->repair_all();		//�������buff
}


/********************************����׶�***********************************/

//��ʼ����
int start()
{
	if(_status != DONE) return -1;

	destruct(load_object(MAP));

	_status = INVITE;
	chat(XIAN, HIG"��ħ������������·����Э����ƽʨ���롣");
	chat(MO, HIR"����ɽ������һ���εģ�����������ħ��ս��");

	remove_call_out("battle_start");
	call_out("battle_start", 2*60);
}

/********************************�����׶�***********************************/

//ս����ʼ
int battle_start()
{
	if (_status != INVITE) return -1;

	//��ʼ����Ӫ
	_camps[XIAN] = ([
		"name"		: "�ɽ�",
		"index"		: XIAN,
		"color"		: HIG,
	]);
	_camps[MO] = ([
		"name"		: "ħ��",
		"index"		: MO,
		"color"		: HIR,
	]);

	_status = BATTLE;
	_start_time = time();
	_time = 0;
	
	rumor("�������Ʈ���ڰ˰���ʨ�����Ͽգ�¡¡ս��Ҳ��ɽ�������\n");

	help_init();
	camp_init();
	camp_accept_all();

	set_heart_beat(PULSE);
	return 1;
}
/********************************���н׶�***********************************/

//����ʤ������PANDING - ��δ����ʤ��
private int calc_winner(int time)
{
	mapping xian = _camps[XIAN];
	mapping mo = _camps[MO];

	if(xian["res"] >= MAX_RES) return XIAN;		//����Դ��
	if(mo["res"] >= MAX_RES) return MO;			//ħ��Դ��
	if(time() - _start_time >= time) {			//��ʱ
		return xian["res"] > mo["res"] ? XIAN : MO;
	}
	return 0;
}

//�������
private void cure_user(object user)
{
	if(user->is_busy() || user->fighting() || user->query("env/invisibility")) return;
	user->receive_curing("kee", HP_CURE);
	user->receive_curing("sen", HP_CURE);
}

//������Ӫ���
void for_camp(mapping camp)
{	
	camp["users"] -= ({ 0 });
	foreach(object who in camp["users"]) {		
		//�����볡���
		object env = environment(who);
		mapping buff = BUFF->find(who, WAIT4R);	//�ȴ������buff
		if(buff || !env || !(env->query("in_bg") || env->query("is_fabao"))) {
			if(!wizardp(who)) room_goto_hell(who);
		}
		//��������ƶ�����
		score_set(who, "mp", PULSE * 2);
		//�������
		cure_user(who);
		reset_eval_cost();
	}
}

//ս��������
void heart_beat()
{
	_time += PULSE;

	//ս��ǰ�ڶ�ʱ���������������
	if(_time < ACCEPT_TIME && _time % INVITE_USER == 0)
		camp_accept_all();

	//���IP
	if(_time % INVITE_USER == PULSE)
		camp_check_ip();
	
	//�ַ�������ë
	if(_time % ALLOT_HAIR == 0) help_allot_hair();

	//����ռ��ݵ㽱��
	foreach(object flag in MAP->flags()) {
		int c = camp_id(flag);
		if(c && !BUFF->find(flag, BG_NO_RES))
			_camps[c]["res"] += FLAG_RES * PULSE;
	}
	
	//����/ż���ȫ�����
	if(_time / PULSE % 2) for_camp(_camps[XIAN]);
	else for_camp(_camps[MO]);

	//����Ƿ������������
	if(calc_winner(MAX_TIME)) stop();
}

/********************************�����׶�***********************************/

//ս������
int stop()
{
	int winner = calc_winner(0);
	_status = DONE;
	set_heart_beat(0);

	rumor(TITLE"�����ˣ�" + camp_name(_camps[winner]) + HIM"ȡ����ʱ��ʤ����\n");
	report(_this, "ʱ��:" + _time + " ʤ��:" + winner);
	
	for(int i = 1; i < sizeof(_camps); ++i) {
		mapping camp = _camps[i];
		int res = camp["res"];
		if(i == winner) res += WIN_POT;
		report(_this, "��Ӫ:" + i + " ��Դ����:" + res);
		//�ַ�����
		foreach(object user in camp["users"]) {
			int exp = score_query(user, "exp");
			int ratio = 100 * score_liveness(user) / 2;		//��Ծ�������ȫ����
			int total = exp + res * truncate(ratio, 30, 100) / 100;
			total = truncate(total, MIN_TOTAL_POT, MAX_TOTAL_POT);

			score_set(user, "exp", total);
			score_add_total(user);
			score_add(user, "times", 1);
			
			if(interactive(user)) score_add_gold(user, total / K / 3);

			reset_eval_cost();
		}
	}
	{
		//�㲥�ɼ� & �˳�
		object* users = sort_user("cmp_kill0");
		broadcast_score(users);

		foreach(object who in users) {
			camp_leave(who);
		}
	}
	//����
	foreach(object flag in MAP->flags()) {
		BUFF->clear(flag);
	}
	return 1;
}

/********************************��������***********************************/

//��ֹupdate������ڴ�й©
int update(string arg)
{
	if(arg == "here") {
		write("ս��npc�����١�\n");
		destruct(_this);
		return 1;
	}
	return 0;
}

//���䷢��
void chat(int camp, string str)
{
	MAP->leaders()[camp]->command("chat " + str);
}

//ҥ������
void rumor(string str)
{
	MAP->leaders()[1]->command("rumor " + str);
}

//��¼
void report(object obj, string msg)
{
	//MONITOR_D->report_system_object_msg(obj, msg + "\n");
}

