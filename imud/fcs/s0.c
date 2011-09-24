// by firefox 04/16/2011
// 

#include "msg.h"
#include "util_s.h"
#include <imud-efun.h>
#include <ansi.h>

/********************************��������***********************************/


#define	MIN_PLAYER				2					//���������
#define	MAX_PLAYER				5					//��������
#define	PLAYER_TIME				60					//���˼��ʱ��
#define BAN_TIME				600					//��;�˳�����ֹ������ʱ��
#define PULSE					6					//����
#define MIN_CHIP				100					//������ٳ�����

/********************************���ػ�����***********************************/

#define ROE						(200*10000/1000)	//���ʣ������뻻1K����
#define DEALER_NAME				"����Ů��"			//

/********************************����***********************************/

#define FAMILY_SKILLS			__DIR__"family-skill"

/********************************���ݶ���***********************************/

int _game_id;					//��ǰ��Ϸid


/********************************��������***********************************/




//��ʼ��
void fcs_init()
{
	_g = ([
		"queue"			: ({}),				//�Ŷ������Ϣ
		"players"		: ({}),				//�����Ϣ(mid, name, id, chip, state, no., bet)

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
	foreach(mapping m in _g["queue"]) {
		m["ready"] = 0;
		m["bet"] = 0;
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
			_g["players"][i]["cards"][j] = _g["cards"][i*MAX_CARD + j];
	}
	dealing();
	return 1;
}

//��Ϸ����
int stop()
{

}


//չʾ���ƹ���
void dealing()
{
	int min_chip = _g["players"][0]["chip"];

	_g["round"]++;
	
	dealer_say("��ʼ���ƣ�\n");
	for(int i = 0; i < players_number(); ++i) {
		mapping who = _g["players"][i];
		show_sb_cards(who);
		//call_out("show_sb_cards", PULSE * (i + 1), _g["players"][i]);
		
		if(who["chip"] < min_chip) min_chip = who["chip"];
	}

	//������ע
	_g["max_bet"] = min_chip / (MAX_CARD  - _g["round"]);

	//������ע˳��
	turn_init();
	_g["bet"] = 0;

	next_one();
}

//����ʤ����
void reward_winner(mapping who)
{
	msv("\n");
	dealer_say("$N��ʤ��\n", who);
	
	who["chip"] += _g["pot"];
	_g["pot"] = 0;

	msv("$N�����ϵĳ���§���Լ���ǰ��\n", who);
}

//����Ӯ��
void finish()
{
	mixed* players = _g["queue"] + _g["players"];

	if(players_number() == 1) {
		reward_winner(_g["players"][0]);
	} else {
		int* max_score = ({-1});
		mapping winner;
		foreach(mapping who in _g["players"]) {
			int* score = cards_score(who["cards"]);
			show_sb_cards(who, 1);
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
	mapping who = turn_who();

	dealer_say("$N�����涨ʱ�䣬�������ơ�\n", who);
	fold(who);
	next_one();
}


//��һ�����
int next_one()
{
	mapping who;

	refresh_look();

	for(int i = 0; i < MAX_PLAYER; ++i) {
		_g["turn"] = (_g["turn"] + 1) % MAX_PLAYER;
		who = turn_who();
		if(who) break;
	}
	remove_call_out("wait_timeout");	
	if(players_number() == 1) {
		finish();
	} else if(!_g["bet"] || who["bet"] < _g["bet"]) {	//��δ��ע����Ҫ�����˵ļ�ע
		
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
	foreach(mapping who in _g["players"]) {
		if(who["no."] == n) return who;
	}
	return 0;
}

//�Ƚ���ұ����ƴ�С
int turn_cmp(int a, int b)
{
	int n = _g["round"];
	return _g["players"][b]["cards"][n] - _g["players"][a]["cards"][n];
}

//��ʼ����һ�֣�������ע˳��
void turn_init()
{
	int n = players_number();
	int* arr = allocate(n);
	
	for(int i = 0; i < n; ++i) {
		_g["players"][i]["bet"] = 0;
		arr[i] = i;
	}
	arr = sort_array(arr, (: turn_cmp :));
	for(int i = 0; i < n; ++i) {
		_g["players"][arr[i]]["no."] = i;
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
mapping find_info(mapping info, mixed* arr)
{
	foreach(mapping m in arr) {
		if(m["mid"] == info["mid"] && m["id"] == info["id"]) return m;
	}
	return 0;
}

//��������Ϣ
mapping this_info()
{	
	return find_info(this_player(), _g["players"]);
}

//��ʾһ����
void show_cards(int* cards);


//��ʾ��Ϣ
varargs int msv1(string msg, mapping me, mapping target, mixed arg);

/********************************״̬���***********************************/

#define CHK_FAIL_STARTED			if(_g["round"] > 0) return notify(MSG_STARTED)
#define CHK_FAIL_NOT_START			if(!_g["round"]) return notify(MSG_NOT_START)
#define CHK_FAIL_NOT_YOU(who)		if(turn_who() != (who)) return notify(MSG_NOT_YOU);
#define CHK_OOC(who, cn)			if(who["chip"] < (cn)) return notify(MSG_NOT_ENOUGH);

#define CHK_CHIP_TOO_LESS(n)		if((n) < 1) return notify(MSG_AT_LEAST_1);
#define CHK_CHIP_TOO_MUCH(n)		if((n) > _g["max_bet"]) return notify(MSG_TOO_MUCH, _g["max_bet"]);

/********************************׼���׶�***********************************/
mapping join(mapping info)
{	
	CHK_FAIL_STARTED;
	
	if(sizeof(_g["queue"]) < MAX_PLAYER) {
		
		mapping who = find_info(info, _g["queue"]);
		if(who) return notify(MSG_JOINED);
		
		who = ([
			"mid"		: info["mid"],
			"id"		: info["id"],
			"name"		: info["name"],
			"chip"		: 0,
			"cards"		: allocate(MAX_CARD),
		]);
		_g["queue"] += ({ who });

		return 1;
	}
	return notify(MSG_FULL);
}

//�볡ѡ���뿪
mapping leave(mapping info)
{
	mapping who = find_info(info, _g["queue"]);

	CHK_FAIL_STARTED;

	if(!who) notify(MSG_NOT_JOIN);

	_g["queue"] -= ({ who });
	
	return who["chip"];
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
mapping ready(mapping info)
{
	mapping who = find_info(info, _g["queue"]);
	
	CHK_FAIL_STARTED;
	if(!who) return notify(MSG_NOT_JOIN);
	if(who["chip"] < MIN_CHIP) return notify(MSG_TOO_LESS, MIN_CHIP);

	who["ready"] = 1;
	
	if(can_start())	start();
	return msgv(MSG_READY);
}

//�����
mapping exchange(mapping info)
{
	mapping who = find_info(info, _g["queue"]);
	int n;
	
	CHK_FAIL_STARTED;
	if(!who) return notify(MSG_NOT_JOIN);
	CHK_OOC(who, n);

	who["chip"] += n;

	return n;
}


/********************************���н׶�***********************************/

//��ע
private int sb_bet(mapping who, int n)
{
	who["chip"] -= n;
	who["bet"] += n;
	_g["pot"] += n;
	if(n > _g["bet"]) _g["bet"] = n;
}

//��ע
mapping bet(mapping info)
{
	mapping who = find_info(info, _g["players"]);

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
mapping call(mapping info)
{
	mapping who = find_info(info, _g["players"]);
	int n;

	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);	
	if(!_g["bet"]) return notify(MSG_PLS_BET);
	n = _g["bet"] - who["bet"];
	CHK_OOC(who, n);

	sb_bet(who, n);
	say(who, "���ˣ�\n\n");

	return next_one();
}

//��ע
mapping raise(mapping info)
{
	mapping who = find_info(info, _g["players"]);
	int add = to_int(arg);
	int n = _g["bet"] + add;
	
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);

	if(!_g["bet"]) return notify(MSG_PLS_BET);
	if(who["bet"] > 0) return notify(MSG_CALL_OR_FOLD);
	CHK_CHIP_TOO_LESS(add);
	CHK_CHIP_TOO_MUCH(n);	
	CHK_OOC(who, n);

	sb_bet(who, n);
	say(who, "��" + add + "��\n\n");

	return next_one();
}

//����
mapping fold(mapping info)
{
	mapping who = find_info(info, _g["players"]);
		
	CHK_FAIL_NOT_START;
	CHK_FAIL_NOT_YOU(who);

	if(!_g["pot"]) return notify(MSG_NO_FOLD);

	_g["queue"] += ({ who });
	_g["players"] -= ({ who });
	
	return next_one();
}

