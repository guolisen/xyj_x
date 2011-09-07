// by firefox 10/01/2010
// ����ɱ-ս����ѭ��

#include "xys.h"
#include "family.c"
#include "card-role.c"
#include "card-weapon.c"

mapping _win_msg = ([
	VIP	+ ZHONG		: "����$N�ξ��л���ȡ���ˣ�����ͽ�ܽ�����ħһ·���С�",
	ZHONG			: "����$N�ξ��л���ȡ���ˣ�������ħһ·���С�",
	JIAN			: "����$N�ξ��а���ȡ����ͽ�ܣ�ǿ��ͨ����뺣�̤��ȡ��·��",
	FAN				: "����$N�ξ��л�����ħ׽��ȡ���������ˡ�",
]);	



object _room;				//

int char_stage;				//��������׶�



/********************************˽�б���***********************************/
int	_status	= DONE;

int _char_tick = 0;			//��Ҽ�ʱ


/********************************��ʼ�׶�***********************************/

//��Ҽ���
int join(string id, int role)
{
	object who = find_player(id);
	mixed* cards = allocate(CARDS_SIZE);
	string family = family_of_random();

	HP->full(who);
	who->move(_this);
	tell_object(who, YEL"�����У�����������һ�����硣\n"NOR);

	_chars[id] = ([
		"id"		: id,
		"name"		: who->query("name"),
		"camp"		: role & 0xff,
		
		"kee"		: 100,
		"sen"		: 100,
		"force"		: 100,
		"mana"		: 100,

		"skills"	: family_skills(family),
		"state"		: allocate(sizeof(_states)),
		"BUFF_PROP"	: ([]),
		"cards"		: cards,
	]);

	cards[0] = _card_roles[role];

	cards[1] = _card_defense;
	cards[2] = family_uskill(family, 0);
	cards[3] = family_uskill(family, 1);
	cards[4] = family_uskill(family, 2);

	cards[5] = _card_unarmed;

	return 1;
}

//����뿪
int leave(string id)
{
	object who = find_player(id);

	if(who && environment(who) == _this) {
		string bed = or2(who->query("dream_place"), "/d/changan/pinqiting");
		HP->full(who);
		who->move(bed);
		tell_object(who, CYN"\n�������۾������˹�����\n\n"NOR);		
	}
	
	//XYS->ip_remove_id(id);
}


//��������볡
int invite_all(string* ids)
{
	if(_status != DONE) return -1;

	_status = BATTLE;
	_start_time = time();

	//�������Ȼ��������
	ids = MATH->shuffle_arr(ids);
	
	join(ids[0], ZHONG + VIP);
	join(ids[1], ZHONG);	
	join(ids[2], JIAN);
	join(ids[3], FAN);
	join(ids[4], FAN);
	join(ids[5], FAN);
	
	//����vip������˵�����
	ids -= ({ ids[0] });
	ids = MATH->shuffle_arr(ids);

	for(int i = 0; i < sizeof(ids); ++i) {
		_chars[ids[i]]["order"] = i + 1;
	}
	
	//��ʼ����
	foreach(string id, mapping m in _chars) {
		for(int i = 0; i < INIT_CARD; ++i) deal(id);
	}	
	return 1;	//�ȴ�������start��������ѭ��
}

//��ʼ��Ϸ
int start(string* ids)
{
	set_heart_beat(PULSE);
	next_one();
}
/********************************���н׶�***********************************/

//����ʤ������PANDING - ��δ����ʤ��
int calc_winner()
{
	if(is_dead(_chars[_vip_id])) {
		if(count_camp(FAN)) return FAN;				//����
		else if(count_camp(ZHONG))return ZHONG;		//�ҳ�
		return JIAN;								//�鳼
	}
	else if(!count_camp(FAN) && !count_camp(JIAN))
		return ZHONG;								//�ҳ�
	return 0;
}

//�Ƿ�����ʤ��
int sb_win()
{
	int winner = calc_winner();
	if(winner) {
		done(winner);
		return 1;
	}
	return 0;
}

//ˢ��״̬
void refresh_state(mapping who)
{
	for(int i = 0; i < sizeof(who["state"]); ++i) {
		if(who["state"][i] > 0) who["state"][i]--;
	}
}

//��һ�����
int next_one()
{
	//������һ������
	_char_tick = 0;
	do {
		_char_no = (_char_no + 1) % sizeof(_chars);
		_char = _chars[_order[_char_no]];
		
	} while(!is_dead(_char));

	//ˢ��buff,״̬
	buff_refresh_all(_char);
	refresh_state();

	//���ʤ������
	if(win()) return 1;
	
	//�����Ҵ���ʧ��״̬��������
	if(out_of_control(_char)) return next_one();
	
	deal(_char);	//���ƣ��ȴ���ҳ���
	return 1;
}

//������Ӫ����
int camp_count(int camp)
{
	int s = 0;
	foreach(string id, mapping who in _chars) {
		if(who["camp"] == camp && !is_dead(who)) s++;
	}
	return s;
}


//ս��������
void heart_beat()
{
	//�������Ƿ��Ѿ��˳�
	foreach(string id, mapping m in _chars) {
		object who = find_player(id);

		//�ӱ�lamster
		if(!who || environment(who) != _room)
			leave(id);

		m["order"] = -1;
	}

	//����Ƿ������������
	if(calc_winner()) stop();

	//��ʾ���ʱ��
	_char_tick++;
	if(_char_tick > CHAR_TIME - 3)
		tell_room(_room, "" + _char_tick);

	//��ʱ����һ����
	if(_char_tick == CHAR_TIME) {
		next_one();
	}
}

/********************************�����׶�***********************************/

//���Ž������볡
void done(int winner)
{
	int duration = time() - _start_time;
	object* winners = ({});

	_status = DONE;
	set_heart_beat(0);

	foreach(string id, mapping m in _chars) {
		object who = find_player(id);
		if(who) {
			who->add(XYS_PROP + "/duration", duration);
			if(m["camp"] & winner) {
				who->add(XYS_PROP + "/win", 1);
				who->add("balance", REWARD_GOLD*10000);
				winners += ({ who });
			}
		}
	}

	if(winner)
		random1(winners)->co	mmand("rumor " + _win_msg[winner] + "\n");	

	foreach(string id, mapping m in _chars) {
		leave(id);
	}
}

//ս������
int stop()
{
	done(calc_winner());
	return 1;
}

/********************************��������***********************************/




//ʧ��״̬
int out_of_control()
{

}

//����
int is_dead(mapping who)
{
	return 1;
}

//���������
int living_count()
{
	int n = 0;
	foreach(string id, mapping who in _chars) {
		n += is_dead(who);
	}
	return n;
}

//����
int deal()
{
	mapping card =([
		"type"		: "��ɫ",
		"name"		: "ȡ����",
		"comment"	: "�������뱻��ɱ�Ķ���",

	]);
	
	//����
	//װ��
	//��ƥ
	//����
	//ҩ��
	
	


}

//��¼
void report(object obj, string msg)
{
	//MONITOR_D->report_system_object_msg(obj, msg + "\n");
}


//������һ�����
mapping find_next(mapping who);

//����ǰһ�����
mapping find_prevous(mapping who);

