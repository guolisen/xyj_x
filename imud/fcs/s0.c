// by firefox 04/16/2011
// fcs server

#include <imud-efun.h>

inherit F_iSERVER;
inherit F_iEFUN;
inherit __DIR__"score";

#include "fcs.h"

/********************************��������***********************************/

#define MAX_CARD				5		//�������
#define	MIN_PLAYER				2		//���������
#define	MAX_PLAYER				4		//��������
#define	PLAYER_TIME				120		//���˼��ʱ��
#define MIN_CHIP				100		//������ٳ�����

/********************************��������***********************************/

int next_one();
void dealing();
void turn_init();
mixed* turn_who();
int fold(mixed* info);
int notify_update_scene();

/********************************���󴴽�***********************************/

//��Ϸ��λ
void data_reset()
{
	_g = ([
		"queue"			: ({}),				//�Ŷ������Ϣ
		"players"		: ({}),				//�����Ϣ(name, id, mud, score, bet/ready, num, cards)

		"round"			: 0,				//�ڼ���
		"turn"			: -1,				//��ǰ������
		"pot"			: 0,				//�ص׳�����
		"bet"			: 0,				//��ǰ��ע
		"max_bet"		: 0,				//������ע����
		"cards"			: allocate(7*4),	//��
		"show_hand"		: 0,				//�Ƿ���������
	]);
}

//����
void create()
{
	server_create();
	data_reset();
}

/********************************���̿���***********************************/

//�������в��������Ϣ
private mixed* find_info(mixed* info, mixed* arr)
{
	foreach(mixed* u in arr) {
		if(u[PMUD] == info[PMUD] && u[PID] == info[PID]) return u;
	}
	return 0;
}

//�����
private int players_number()
{
	return sizeof(_g["players"]);
}


//��Ϸ��ʼ
int start()
{
	foreach(mixed* u in _g["queue"]) {
		u[PREADY] = 0;
	}
	_g["players"] = _g["queue"];
	_g["queue"] = ({});

	//ϴ��
	for(int i = 0; i < sizeof(_g["cards"]); ++i) {
		_g["cards"][i] = i;
	}
	shuffle(_g["cards"]);

	//����
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
	int n = _g["pot"] / players_number();
	foreach(mixed* who in _g["players"]) {
		who[PSCORE] += n;
		notify_all("on_leave", who);
	}
	data_reset();
	ICE_D->flush();
}

//���ƹ���
void dealing()
{
	int min_chip = _g["players"][0][PSCORE];

	_g["round"]++;		
	for(int i = 0; i < players_number(); ++i) {
		mixed* u = _g["players"][i];
		if(u[PSCORE] < min_chip) min_chip = u[PSCORE];		//ÿ�ֶ�ע����
	}
	_g["max_bet"] = min_chip / (MAX_CARD  - _g["round"]);

	//��ʼ����һ��
	turn_init();

	notify_update_scene();
	notify_all("on_dealing");
	next_one();
}

//�����Ϸ������Ӯ��
void finish()
{
	mixed* all = _g["queue"] + _g["players"];
	mixed* winner, arg;

	if(players_number() == 1) {
		winner = _g["players"][0];
	} else {
		int* max_score = ({-1});
		string* arr = allocate(players_number());

		for(int i = 0; i < players_number(); ++i) {
			mixed* who = _g["players"][i];
			int* score = cards_score(who[PCARDS]);
			arr[i] = score_name(score[0]);
			if(cmp_score(score, max_score) > 0) {
				max_score = score;
				winner = who;
			}
			who[PREADY] = 0;
		}
		arg = implode(arr, ":");	//��ȡ�����Ƶ�����
		_g["show_hand"] = 1;		//����
		notify_update_scene();
	}
	//����ʤ��
	winner[PSCORE] += _g["pot"];
	_g["pot"] = 0;
	//����
	data_reset();	
	_g["queue"] = all;

	notify_all("on_finish", winner, arg);
}

//��ҳ�ʱ
void wait_timeout()
{
	mixed* who = turn_who();
	
	_g["queue"] += ({ who });
	_g["players"] -= ({ who });

	notify_all("on_timeout", who);
	next_one();
}

//��һ�����
int next_one()
{
	mixed* who;	
	
	for(int i = 0; i < MAX_PLAYER; ++i) {
		_g["turn"] = (_g["turn"] + 1) % MAX_PLAYER;
		who = turn_who();
		if(who) break;
	}
	remove_call_out("wait_timeout");	
	if(players_number() == 1) {
		finish();
	} else if(!_g["bet"] || who[PBET] < _g["bet"]) {	//��δ��ע����Ҫ�����˵ļ�ע
		notify_all("on_next_one", who);
		call_out("wait_timeout", PLAYER_TIME);
	} 
	else if(_g["round"] < MAX_CARD - 1) {
		dealing();	//����next_one->dealing->next_one
	} else {
		finish();
	}
	notify_update_scene();
	ICE_D->flush();
	return 1;
}

/********************************��ע˳��***********************************/

//��ǰ�ֵ������
mixed* turn_who()
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

//��ʼ����һ�֣�	������ע˳��
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
	_g["bet"] = 0;
}

/********************************״̬���***********************************/

#define CHK_FAIL_STARTED			if(_g["round"] > 0) return notify(info, MSG_STARTED)
#define CHK_FAIL_NOT_START			if(!_g["round"]) return notify(info, MSG_NOT_START)
#define CHK_FAIL_NOT_YOU(who)		if(turn_who() != (who)) return notify(info, MSG_NOT_YOU);
#define CHK_OOC(who, cn)			if(who[PSCORE] < (cn)) return notify(info, MSG_NOT_ENOUGH);

#define CHK_CHIP_TOO_LESS(n)		if((n) < 1) return notify(info, MSG_AT_LEAST_1);
#define CHK_CHIP_TOO_MUCH(n)		if((n) > _g["max_bet"]) return notify(info, MSG_TOO_MUCH, _g["max_bet"]);

/********************************׼���׶�***********************************/
///��Ҽ���
int join(mixed* info)
{
	CHK_FAIL_STARTED;
	
	if(sizeof(_g["queue"]) < MAX_PLAYER) {		
		mixed* who = find_info(info, _g["queue"]);
		if(who) return notify(info, MSG_JOINED);		
		who = ({
			info[PNAME],
			info[PID],
			info[PMUD],
			0,					//PSCORE
			0,					//PREADY
			0,					//PNUM
			allocate(MAX_CARD)
		});
		_g["queue"] += ({ who });
		
		call_out("ready_timeout", PLAYER_TIME, who);
		
		notify_update_scene();
		notify_all("on_join", info);
		return ICE_D->flush();
	}
	return notify(info, MSG_FULL);
}

//�볡ѡ���뿪
int leave(mixed* info)
{
	mixed* who = find_info(info, _g["queue"]);

	CHK_FAIL_STARTED;

	if(!who) notify(info, MSG_NOT_JOIN);

	_g["queue"] -= ({ who });
	
	notify_update_scene();
	notify_all("on_leave", info, who[PSCORE]);
	return ICE_D->flush();
}

//���join��δ�ܼ�ʱready
void ready_timeout(mixed* info)
{
	mixed* who = find_info(info, _g["queue"]);
	if(who) leave(who);
}

//�Ƿ���Կ�ʼ
private int can_start()
{
	//�ж��ɷ�ʼ
	if(sizeof( _g["queue"]) < MIN_PLAYER) return 0;
	foreach(mapping m in _g["queue"]) {
		if(!m[PREADY]) return 0;
	}
	return 1;
}

//�볡ѡ����������
int ready(mixed* info)
{
	mixed* who = find_info(info, _g["queue"]);
	
	CHK_FAIL_STARTED;
	if(!who) return notify(info, MSG_NOT_JOIN);
	if(who[PSCORE] < MIN_CHIP) return notify(info, MSG_TOO_LESS, MIN_CHIP);

	who[PREADY] = 1;
	
	notify_all("on_ready", info);
	if(can_start()) start();
	else {
		notify_update_scene();
		return ICE_D->flush();
	}
	return 1;
}

//�����
int exchange(mixed* info, string arg)
{
	mixed* who = find_info(info, _g["queue"]);
	int n = to_int(arg);
	
	CHK_FAIL_STARTED;
	if(!who) return notify(info, MSG_NOT_JOIN);
	CHK_OOC(who, -n);

	who[PSCORE] += n;

	notify_update_scene();
	notify_all("on_exchange", info, n);
	return ICE_D->flush();
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
int bet(mixed* info, string arg)
{
	mixed* who = find_info(info, _g["players"]);
	int n = to_int(arg);
		
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);	
	if(_g["bet"]) return notify(info, MSG_BETTED);
	CHK_CHIP_TOO_LESS(n);
	CHK_CHIP_TOO_MUCH(n);
	CHK_OOC(who, n);

	sb_bet(who, n);	

	notify_all("on_bet", info, n);

	return next_one();
}

//��ע
int call(mixed* info)
{
	mixed* who = find_info(info, _g["players"]);
	int n;

	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);	
	if(!_g["bet"]) return notify(info, MSG_PLS_BET);
	n = _g["bet"] - who[PBET];
	CHK_OOC(who, n);

	sb_bet(who, n);

	notify_all("on_call", info, n);

	return next_one();
}

//��ע
int raise(mixed* info, string arg)
{
	mixed* who = find_info(info, _g["players"]);
	int add = to_int(arg);
	int n = _g["bet"] + add;
	
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);

	if(!_g["bet"]) return notify(info, MSG_PLS_BET);
	if(who[PBET] > 0) return notify(info, MSG_CALL_OR_FOLD);
	CHK_CHIP_TOO_LESS(add);
	CHK_CHIP_TOO_MUCH(n);	
	CHK_OOC(who, n);

	sb_bet(who, n);

	notify_all("on_raise", info, n + ":" + add);

	return next_one();
}

//��ʾ����
int show_hand(mixed* info, string arg)
{
	mixed* who = find_info(info, _g["players"]);
	int n = _g["max_bet"];
	
	if(_g["round"] < MAX_CARD - 1) return notify(info, MSG_NOT_LAST);

	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);
	CHK_OOC(who, n);

	sb_bet(who, n);
	notify_all("on_show_hand", info, n);

	return next_one();

}


//����
int fold(mixed* info)
{
	mixed* who = find_info(info, _g["players"]);
		
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);

	if(!_g["pot"]) return notify(info, MSG_NO_FOLD);

	_g["queue"] += ({ who });
	_g["players"] -= ({ who });

	notify_all("on_fold", info);
	
	return next_one();
}

//�鿴�Լ��ĵ���
int look_card(mixed* info)
{
	mixed* who = find_info(info, _g["players"]);

	CHK_FAIL_NOT_START;

	if(!who) return notify(info, MSG_NO_HAND_CARD);
	
	reply(_client, "on_look_card", info, who[PCARDS][0]);
	return ICE_D->flush();
}

/********************************��������***********************************/

//����������л����ַ���
string code_player(mixed* u)
{
	int* cards = allocate(_g["round"] + 1);

	for(int i = 0; i < sizeof(cards); ++i) {
		cards[i] = u[PCARDS][i];
	}
	if(!_g["show_hand"]) cards[0] = 29;
	return sprintf("%s:%s:%s:%d:%s",
		u[PNAME],
		u[PID],
		u[PMUD],
		u[PSCORE],
		to_base64(cards)
	);
}

//�����������л����ַ���
string code_scene()
{
	string s1 = sprintf("%d;%d",_g["pot"], players_number());
	string s2 = "";
	string s3 = "";
	foreach(mixed* u in _g["players"]) {
		s2 += ";" + code_player(u);
	}
	foreach(mixed* u in _g["queue"]) {
		s3 += ";" + code_player(u);
	}
	return s1 + s2 + s3;
}

//������³���
int notify_update_scene()
{
	notify_all("on_update_scene", 0, code_scene());
}
