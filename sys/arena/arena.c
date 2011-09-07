// by firefox 11/21/2009

inherit NPC;

#include "arena.h"
#include "cmds.c"


mapping* _camps = ({0, ([]), ([]),});


void create()
{
	seteuid(getuid());
	_status	= DONE;
}


//��ʼ����
void start()
{

	if(_status != DONE) return -1;

	_status = INVITE;

	chat(HIG TITLE + "������ʼ��������ǰ��������");

	remove_call_out("battle_start");
	call_out("battle_start", 2*60);

	//�����׶�
	//���ѡ���ʸ�ͨ����
	
	//��ʼ

	//��̭������
	//����
	//����

	//��������������˳��


}

//С������ʼ
int group_start(int n)
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
	
	rumor("С������1�ֿ�ʼ��\n");

	help_init();
	camp_init();
	camp_accept_all();

	set_heart_beat(PULSE);

	//�ж��Ƿ����ǰ����

	if()
		group_start(n++);
	else
		final_start();

	return 1;
}

//������ʼ
int final_start()
{
	//��ʼ�������ɵı���
	battle_start(mapping );
}

//���ӿ�ս��ս���������ͽ��
int battle_start(mapping team1, mapping team2);
{

}

//����ս���������㱨ʤ����
int battle_end()
{}


//����ս������
int process()
{
	//��ǰ�����Ƿ������û������ȴ�

	if(_status == GROUP)
	//С�����Ƿ������
		//����С����
	
	if(_status == FINAL)
	//�����Ƿ������
		//���ž���

	//���Ž���
}


//��ֹ����
void stop()
{
	chat(TITLE + "��ʽ��Ļ��");
	//�������
}




mapping _teams = ([			//������������
	"nmj"		: ([
		"firefox"	: 1000,
		"laipi"	: 1000,
		"laipi"	: 1000,
	])
]);

mixed* _table = ({});		//���̰���

int do_join(string arg)
{
	string* arr = str_split(arg, ' ');
	foreach(string id in arr) {
		object player = find_player(id);
		//�����ɣ���¼����
	}
	
}

//��鹤��ñ
void valid()
{	
	mapping exps = ([]);		//����ƽ��exp
	int sum = 0;				//����ƽ��exp֮��
	int avg = 0;				//����ƽ��exp�ľ�ֵ

	foreach(string tid, mapping team in _teams) {
		int s = 0;
		foreach(string id, int exp in team) {
			s += exp;
		}
		exps[tid] = s / MAX_NUMBER;
		sum += exps[tid];
	}
	avg = sum / sizeof(_teams);

	{	//ɸѡ��������ñ�Ķ���
		int max_exp = avg * MAX_EXP_RATIO / 100;
		foreach(string tid, int exp in exps) {
			if(exp > max_exp) {
				string* arr = keys(_teams[tid]);
				string uid = random1(arr);
				object player = find_player(uid);
				map_delete(_teams[tid], uid);
				if(player) {
					_this->command("chat ɾ��");
				}
				
			}
		}
	}

	{	//������
		int n = sizeof(_teams);
		string* arr = shuffle(_teams);	//������и���
		string* places = shuffle(places);	//������������
		string winners = ({});
		mapping schedule = ();

		if(n % 2) {	//�����������һ��
			winners += ({arr[n - 1]});
		}
		for(int i = 0; i < n/2; ++i) {
			schedule[places[i]] = ({arr[i*2], arr[i*2+1]})
		}
	}
	{
		//������̨����

		//��̨���󣬿�ʼ�����λ�ã���������ʱƽ��
		
		//ÿ�ֱ�����������鱾���Ƿ����
		
	}

}
