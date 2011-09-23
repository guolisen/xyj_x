// by firefox 04/16/2011
// 

#include "msg.h"
#include <imud-efun.h>

#include "util_s.h"

#include <ansi.h>



/********************************��������***********************************/

#define MAX_CARD				5					//����������
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

mapping _g;						//ȫ������
object_f _localizer;			//���ػ�����
mapping _dealer;				//������
int _game_id;					//��ǰ��Ϸid
object_f _stand;				//��̨

/********************************��������***********************************/


//��ȡ�������
varargs mixed data_of(object who, string prop)
{
	string root = _localizer->get("prop_root");
	mapping m = who->query(root);
	if(!mapp(m)) who->set(root, m = ([]));
	return prop ? m[prop] : m;
}

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

	_localizer	= __DIR__"localizer";
	_dealer		= ([]) + _localizer->get("dealer");
	_game_id	= path_file(__FILE__)[0] - '0';
	_stand		= __DIR__"stand" + _game_id;
}

mixed g()
{
	return _g;
}

//�����
int players_number()
{
	return sizeof(_g["players"]);
}




//�볡
int leave(string arg)
{

}


//ĳ�˾���
int sb_ready(string gid)
{
}



//��ע
int call(string arg)
{
}

//��ע
int raise(string arg)
{}




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




/********************************Զ�̽ӿ�***********************************/

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
	object ob = this_player();
	mapping who = find_info(ob, _g["queue"]);

	CHK_FAIL_STARTED;

	if(!who) notify(MSG_NOT_JOIN);

	//wait for

	if(who["chip"] > 0) {
		_localizer->exchange_chip(this_player(), -who["chip"]);
		msv("$N�˵��˳��롣\n", who);
	}
	_g["queue"] -= ({ who });
	msv("$N�����뿪�����ӡ�\n\n", who);
	refresh_look();
	ob->move(_stand);
	ob->save();
	return 1;
}
