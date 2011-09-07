#ifndef SYS_ALX_H_INCLUDED
#define SYS_ALX_H_INCLUDED
// by firefox 10/01/2010
// 

#include <ansi.h>
#include <xyj_x.h>

/********************************��������***********************************/

#define TITLE					"���лþ�"

#define	PULSE					2					//����

#define BATTLE					1
#define DONE					2


#define	MIN_CHAR				4					//���������
#define	MAX_CHAR				6					//��������
#define INIT_CARD				4					//��ʼ��Ҿ��е�����

#define INIT_TIME				5					//��ʼ���ƺ���ҵ�˼��ʱ��
#define	CHAR_TIME				8					//���˼��ʱ��

#define REWARD_GOLD				10					//ʤ�������Ļƽ�
#define BAN_TIME				600					//��;�˳�����ֹ������ʱ��

#define CARDS_SIZE				16					//����������
#define BASIC_CARDS				6					//��������
#define FLOW_CARDS				5					//�����������


/********************************����***********************************/

#define FAMILY_SKILLS			__DIR__"family-skill"

/********************************�������***********************************/

#define C_ROLE					0					//
#define C_WEAPON				4					//
#define C_CLOTH					5					//
#define C_HORSE					6					//
#define EQU_PROP				"equ_prop"

/********************************��ҽ�ɫ***********************************/

#define VIP						256					//������־
#define ZHONG					1					//�ҳ�
#define ZHU						(ZHONG + VIP)		//����
#define	JIAN					2					//�鳼
#define	FAN						4					//����

mapping _roles = ([
	ZHU			: "ȡ����",
	ZHONG		: "ͽ��",
	JIAN		: "��ͽ��",
	FAN			: "����",
]);

/********************************���״̬***********************************/

#define S_BUSY					0
#define S_NO_MOVE				1
#define S_NO_CAST				2
#define S_NO_WIELD				3
#define S_NO_CONTROL			4
#define S_NO_POWERUP			5
#define S_NOT_HERE				6

mixed* _states = ({
	({ "�Թ˲�Ͼ",	"���ܹ���/ʩ����" }),
	({ "�����ƶ�",	"�����ƶ�/����" }),
	({ "����ʩ��",	"����ʩ��" }),
	({ "���ñ���",	"����ʹ�ñ���" }),
	({ "ʧ��",		"����ʧ��״̬" }),
	({ "��ֹǿ��",	"����ʹ��ǿ������" }),
	({ "����ս��",	"����ս���ֳ�" }),
});


/********************************��������***********************************/

mapping _chars = ([]);								//�������
string* _order = ({});								//��ҵ�ǰ����
int _char_no = -1;									//��ǰ��ұ��
mapping _char;										//��ǰ�������

int _start_time;									//ս������ʱ��

/********************************��������***********************************/

//��ʾ��Ϣ
varargs int msv1(string msg, mapping me, mapping target, mixed arg);
//�ж�����Ƿ�����
int is_dead(mapping who);

//��������
string weapon_type(mapping me);

#define _who _chars[getuid(_player)]				//����ĵ�ǰ�û�������


//һ�㷨����������
int cast(mapping card, mapping me, mapping target);
//һ������������
int perform(mapping card, mapping me, mapping target);
/*

//һ����ǿ����
int powerup(mapping card, mapping me, mapping target);
//Ⱥ�巨����������
int aoe(mapping card, mapping me, mapping target);
//һ�㷨�������ж�
int cast_success(mapping card, mapping me, mapping target);
*/


//���һ��buff
int buff_add(mapping who, mapping buff);
//ˢ�²�����buff��ʣ��ʱ��
int buff_refresh(mapping buff);
//�Ƴ�һ��buff
int buff_remove(mapping buff);
//ˢ��ĳ�˵�ȫ��buff���Ƴ�����buff
void buff_refresh_all(mapping who);


//ж�����������
int unequip(mapping who, int n);
//װ�����������
int equip(mapping who, int n);

//������һ�����
mapping find_next(mapping who);
//����ǰһ�����
mapping find_prevous(mapping who);

//���ѡ�����ɣ������似��
mapping skill_of_random();
//����ע��
string skill_comment(string skill);

#endif


/*

_chars�����ݽṹ


	//������ݽṹ

	name				//����
	id					//id
	order				//���
	camp				//��Ӫ
	turn				//����
	[hp]
		max_kee/kee
		max_sen/sen
		max_mana/mana
		max_force/force
	skills
		parry
		dodge	
		force
		spells
		unarmed	
		stick
	apply
		damage
		dodge
	state
		no_move		//���ܶ�������������
		busy		//������
	buff
		+damage
		dot
	cards
		role
			vip			apply/max_kee	100
		family
			pili		weapon : stick, force : 20
			thuder		mana : 20,	success 50 damage 30
			ding		mana : 20,
		equip
			weapon		�𹿰�(133)
			cloth		���ʥ��(33)
			horse		������(75)
		misc
			fabao
			drug
			
*/