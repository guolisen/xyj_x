// by firefox 04/16/2011
// 

#include "msg.h"
#include "util_s.h"
#include "score.c"
#include <imud-efun.h>
#include <ansi.h>

/********************************��������***********************************/


#define	MIN_PLAYER				2					//���������
#define	MAX_PLAYER				5					//��������
#define	PLAYER_TIME				120					//���˼��ʱ��
#define BAN_TIME				600					//��;�˳�����ֹ������ʱ��
#define PULSE					6					//����
#define MIN_CHIP				100					//������ٳ�����


#define PREADY					4					//����Ƿ����
#define PBET					4					//��ұ���Ͷע��
#define PNUM					5					//������
#define PCARDS					6					//��ҵ���


/********************************���ػ�����***********************************/

#define ROE						(200*10000/1000)	//���ʣ������뻻1K����
#define DEALER_NAME				"����Ů��"			//

/********************************����***********************************/

#define FAMILY_SKILLS			__DIR__"family-skill"

/********************************���ݶ���***********************************/

int _game_id;					//��ǰ��Ϸid


/********************************��������***********************************/


int next_one();
void reward_winner(mixed* who);
int start();

/********************************��������***********************************/





//��ʼ��
void fcs_init()
{
	_g = ([
		"queue"			: ({}),				//�Ŷ������Ϣ
		"players"		: ({}),				//�����Ϣ(name, id, mud, score, bet/ready, num, cards)

		"round"			: 0,				//�ڼ���
		"turn"			: -1,				//��ǰ������
		"timeout"		: 0,				//��ǰ����Ƿ�ʱ
		"pot"			: 0,				//�ص׳�����
		"bet"			: 0,				//��ǰ��ע
		"max_bet"		: 0,				//������ע����
		"cards"			: allocate(7*4),	//��
	]);

	_game_id	= path_file(__FILE__)[0] - '0';

}

//�����
int players_number()
{
	return sizeof(_g["players"]);
}

//��Ϸ��ʼ
int start()
{
	foreach(mixed* u in _g["queue"]) {
		u[UREADY] = 0;
	}
	_g["players"] = _g["queue"];
	_g["queue"] = ({});

	//ϴ��
	for(int i = 0; i < sizeof(_g["cards"]); ++i) {
		_g["cards"][i] = i;
	}
	shuffle(_g["cards"]);

	//�������
	for(int i = 0; i < players_number(); ++i) {
		for(int j = 0; j < MAX_CARD; ++j)
			_g["players"][i][PCARDS][j] = _g["cards"][i*MAX_CARD + j];
	}
	dealing();
	return 1;
}

//ǿ�ƽ�����Ϸ
int stop()
{
	//ƽ��/�˻����룬�볡
	int n = _g["pot"] / sizeof(_g["players"]);
	foreach(mixed* who in _g["players"]) {
		who[USCORE] += n;
		send_req("on_leave", who);
	}
}


//չʾ���ƹ���
void dealing()
{
	int min_chip = _g["players"][0][PSCORE];

	_g["round"]++;
	
	dealer_say("��ʼ���ƣ�\n");													//todo
	for(int i = 0; i < players_number(); ++i) {
		mixed* who = _g["players"][i];
		show_sb_cards(who);
		//call_out("show_sb_cards", PULSE * (i + 1), _g["players"][i]);
		
		if(who[PSCORE] < min_chip) min_chip = who[PSCORE];
	}

	//������ע
	_g["max_bet"] = min_chip / (MAX_CARD  - _g["round"]);

	//������ע˳��
	turn_init();
	_g["bet"] = 0;

	next_one();
}

//����ʤ����
void reward_winner(mixed* who)
{
	who[PSCORE] += _g["pot"];
	_g["pot"] = 0;

	send_req("on_reward_winner");
}

//����Ӯ��
void finish()
{
	mixed* players = _g["queue"] + _g["players"];

	if(players_number() == 1) {
		reward_winner(_g["players"][0]);
	} else {
		int* max_score = ({-1});
		mixed* winner;
		foreach(mixed* who in _g["players"]) {
			int* score = cards_score(who[PCARDS]);

			show_sb_cards(who, 1);							//todo
			dealer_say(_score_name[score[0]] + "!\n");
			
			if(cmp_score(score, max_score) > 0) {
				max_score = score;
				winner = who;
			}
		}
		reward_winner(winner);
	}	

	fcs_init();	
	_g["queue"] = players;

	refresh_look();
}

//��ҳ�ʱ
void wait_timeout()
{
	mixed* who = turn_who();

	dealer_say("$N�����涨ʱ�䣬�������ơ�\n", who);
	fold(who);
	next_one();
}


//��һ�����
int next_one()
{
	mixed* who;

	refresh_look();

	for(int i = 0; i < MAX_PLAYER; ++i) {
		_g["turn"] = (_g["turn"] + 1) % MAX_PLAYER;
		who = turn_who();
		if(who) break;
	}
	remove_call_out("wait_timeout");	
	if(players_number() == 1) {
		finish();
	} else if(!_g["bet"] || who[PBET] < _g["bet"]) {	//��δ��ע����Ҫ�����˵ļ�ע
		
		dealer_say("$N������ע��\n", who);
		call_out("wait_timeout", PLAYER_TIME);		//todo:
	} 
	else if(_g["round"] < MAX_CARD - 1) {
		dealing();
	} else {
		finish();
	}
	return 1;
}






//����Ӯ��
void calc_winner()
{
}
/********************************��ע˳��***********************************/



//�ֵ���ǰ
mapping turn_who()
{
	int n = _g["turn"];
	foreach(mixed* who in _g["players"]) {
		if(who[PNUM] == n) return who;
	}
	return 0;
}

//�Ƚ���ұ����ƴ�С
int turn_cmp(int a, int b)
{
	int n = _g["round"];
	return _g["players"][b][PCARDS][n] - _g["players"][a][PCARDS][n];
}

//��ʼ����һ�֣�������ע˳��
void turn_init()
{
	int n = players_number();
	int* arr = allocate(n);
	
	for(int i = 0; i < n; ++i) {
		_g["players"][i][PBET] = 0;
		arr[i] = i;
	}
	arr = sort_array(arr, (: turn_cmp :));
	for(int i = 0; i < n; ++i) {
		_g["players"][arr[i]][PNUM] = i;
	}
	_g["turn"] = -1;
}
/********************************��������***********************************/





//��ȡ����Ҵ���������Ϣ��ID
string gid(object who)
{
	return getuid(who) + "@" + MUD_ID;
}

//���������Ϣ
mixed* find_info(mixed* info, mixed* arr)
{
	foreach(mixed* u in arr) {
		if(u[PMUD] == info[PMUD] && u[PID] == info[PID]) return u;
	}
	return 0;
}


//��ʾһ����
void show_cards(int* cards);


//��ʾ��Ϣ
varargs int msv1(string msg, mapping me, mapping target, mixed arg);


/********************************״̬���***********************************/

/********************************״̬���***********************************/

#define CHK_FAIL_STARTED			if(_g["round"] > 0) return notify(MSG_STARTED)
#define CHK_FAIL_NOT_START			if(!_g["round"]) return notify(MSG_NOT_START)
#define CHK_FAIL_NOT_YOU(who)		if(turn_who() != (who)) return notify(MSG_NOT_YOU);
#define CHK_OOC(who, cn)			if(who[PSCORE] < (cn)) return notify(MSG_NOT_ENOUGH);

#define CHK_CHIP_TOO_LESS(n)		if((n) < 1) return notify(MSG_AT_LEAST_1);
#define CHK_CHIP_TOO_MUCH(n)		if((n) > _g["max_bet"]) return notify(MSG_TOO_MUCH, _g["max_bet"]);

/********************************׼���׶�***********************************/
///��Ҽ���
int join(mixed* info)
{
	CHK_FAIL_STARTED;
	
	if(sizeof(_g["queue"]) < MAX_PLAYER) {		
		mixed* who = find_info(info, _g["queue"]);
		if(who) return notify(MSG_JOINED);		
		who = ({
			info[PNAME],
			info[PID],
			info[PMUD],
			info[PSCORE],
			0,					//PREADY
			0,					//PNUM
			allocate(MAX_CARD)
		});
		_g["queue"] += ({ who });

		return refresh_all(info);
	}
	return notify(info, MSG_FULL);
}

//�볡ѡ���뿪
mapping leave(mixed* info)
{
	mixed* who = find_info(info, _g["queue"]);

	CHK_FAIL_STARTED;

	if(!who) notify(MSG_NOT_JOIN);

	_g["queue"] -= ({ who });
	
	return who[PSCORE];
}

//�Ƿ���Կ�ʼ
private int can_start()
{
	//�ж��ɷ�ʼ
	if(sizeof( _g["queue"]) < MIN_PLAYER) return 0;
	foreach(mapping m in _g["queue"]) {
		if(!m["ready"]) return 0;
	}
	return 1;
}

//�볡ѡ����������
mapping ready(mixed* info)
{
	mixed* who = find_info(info, _g["queue"]);
	
	CHK_FAIL_STARTED;
	if(!who) return notify(MSG_NOT_JOIN);
	if(who[PSCORE] < MIN_CHIP) return notify(MSG_TOO_LESS, MIN_CHIP);

	who["ready"] = 1;
	
	if(can_start())	start();
	return msgv(MSG_READY);
}

//�����
mapping exchange(mixed* info)
{
	mixed* who = find_info(info, _g["queue"]);
	int n;
	
	CHK_FAIL_STARTED;
	if(!who) return notify(MSG_NOT_JOIN);
	CHK_OOC(who, n);

	who[PSCORE] += n;

	return n;
}


/********************************���н׶�***********************************/

//��ע
private int sb_bet(mixed* who, int n)
{
	who[PSCORE] -= n;
	who[PBET] += n;
	_g["pot"] += n;
	if(n > _g["bet"]) _g["bet"] = n;
}

//��ע
mapping bet(mixed* info)
{
	mixed* who = find_info(info, _g["players"]);

	int n = to_int(arg);
	
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);	
	if(_g["bet"]) return notify(MSG_BETTED);
	CHK_CHIP_TOO_LESS(n);
	CHK_CHIP_TOO_MUCH(n);
	CHK_OOC(who, n);

	sb_bet(who, n);	
	say(who, n + "!\n");

	return next_one();
}

//��ע
mapping call(mixed* info)
{
	mixed* who = find_info(info, _g["players"]);
	int n;

	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);	
	if(!_g["bet"]) return notify(MSG_PLS_BET);
	n = _g["bet"] - who[PBET];
	CHK_OOC(who, n);

	sb_bet(who, n);
	say(who, "���ˣ�\n\n");

	return next_one();
}

//��ע
mapping raise(mixed* info)
{
	mixed* who = find_info(info, _g["players"]);
	int add = to_int(arg);
	int n = _g["bet"] + add;
	
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);

	if(!_g["bet"]) return notify(MSG_PLS_BET);
	if(who[PBET] > 0) return notify(MSG_CALL_OR_FOLD);
	CHK_CHIP_TOO_LESS(add);
	CHK_CHIP_TOO_MUCH(n);	
	CHK_OOC(who, n);

	sb_bet(who, n);
	say(who, "��" + add + "��\n\n");

	return next_one();
}

//����
mapping fold(mixed* info)
{
	mixed* who = find_info(info, _g["players"]);
		
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);

	if(!_g["pot"]) return notify(MSG_NO_FOLD);

	_g["queue"] += ({ who });
	_g["players"] -= ({ who });
	
	return next_one();
}

