
// by firefox 10/01/2010
// ����ɱ-װ��

#include "xys.h"

/*

mapping card = ([		//card���ݽṹ

	"type"			:	//���
	"name"			:	//����
	"comment"		:	//˵��

	//ʹ������

	"cd_prop"		:	//��ȴ����
	"cd"			:	//��ȴʱ��

	"cost_prop"		:	//��������
	"cost"			:	//������ֵ
	
	"no_target"		:	//����ָ��Ŀ��
	"need_weapon"	:	//Ҫ�����ʹ��ָ�����͵�����
	
	"add"			:	//ʹ��ʱ���������ֵ����
	
	"fun"			:	//���ܺ���
	"dist"			:	//��Ч����
	"success"		:	//��������ϵ��

	"msg_start"		:	//��ʼ��ʾ��Ϣ
	"msg_ok"		:	//�ɹ���ʾ��Ϣ
	"msg_fail"		:	//ʧ����ʾ��Ϣ
	"msg_eff"		:	//��Чʱ��ʾ����aoe,dot

	"d_type"	:	//�����˺����ͣ�1-��Ѫ��2-����3-����
	"damage"		:	//�˺�ֵ
	"aoe_all"		:	//aoe�˺������ˣ�����ʩ����

	"use_once"		:	//һ���ԣ��ù�������

	//������װ������

	"slot"			:	//��װλ��
	EQU_PROP		:	//��������
	"skill_type"	:	//�����Ķ�Ӧ����
]);

*/

//����һ����λ��
private int empty_slot(mapping who)
{
	for(int i = BASIC_CARDS; i < CARDS_SIZE; ++i) {
		if(!who["cards"][i]) return i;
	}
	return CARDS_SIZE;
}

//ж�����������
int unequip(mapping who, int n)
{
	mapping cards = who["cards"];
	mapping card = cards[n];
	int slot = card["slot"];
	
	if(slot != n) return 0;		//û��װ��
	
	//�Ƴ�apply
	foreach(string k, int v in card[EQU_PROP]) {
		who["apply"][k] -= v;
	}	
	cards[empty_slot(who)] = card;
	cards[n] = 0;
	return 1;
}


//װ�����������
int equip(mapping who, int n)
{
	mapping cards = who["cards"];
	mapping card = cards[n];
	int slot = card["slot"];					//װ����װλ��
	mapping old = cards[slot];
	
	if(card == old) return 1;
	if(!card[EQU_PROP]) return 0;			//����װ��

	if(old) unequip(who, slot);

	cards[slot] = card;

	//����apply
	foreach(string k, int v in card[EQU_PROP]) {
		who["apply"][k] += v;
	}
	return 1;
}

//������һ�����
private int movement(mapping who)
{
	int* s = who["state"];
	if(s[S_NO_MOVE] || s[S_BUSY] || s[S_NO_CONTROL]) return 0;
	return who["apply"]["movement"];
}

//������Ҽ����
private int dist(mapping who, mapping target)
{
	int n = (target["order"] - who["order"] + MAX_CHAR) % MAX_CHAR;
	
	if(n > MAX_CHAR / 2) n = MAX_CHAR - n;
	return n;	
}

//ʹ�ÿ�Ƭ
mixed use(mapping who, int n, mapping target)
{
	mapping cards = who["cards"];
	mapping card = cards[n];
	mapping add = card["add"];						//������������ҩ��
	function fun = card["fun"];						//����
	int ok = 0;
	int cdp = card["cd_prop"];
	string cop = card["cost_prop"];

	//���Ŀ��
	if(!card["no_target"] && !target) return "δָ��Ŀ�ꡣ";
	//���CD
	if(cdp && who["state"][cdp]) return card["name"] + "��ʱ�����á�";
	//�����������
	if(card["need_weapon"] && card["need_weapon"] != weapon_type(who))
		return "ȱ�ٺ��ʵ�������";
	//�������	
	if(cop) {
		if(who[cop] < card["cost"]) return "��״̬���ѡ�";		
		who[cop] -= card["cost"];
	}
	msv1(card["msg_start"], who, target, card);

	//���ƻ�������������
	if(add) {
		foreach(string k, int v in add) {
			who[k] = min2(who[k] + v, 100);
		}
		ok = 1;
	}
	//�����⹦�ܵ���Ʒ
	if(fun) {		
		int d = dist(who, target) + movement(who) - movement(target);
		
		if(!card["no_target"] && card["dist"] < d) return "����Ŀ��̫Զ��";
		ok = evaluate(fun, card, who, target);	//���ؼ����Ƿ�ɹ�
	}
	//��ʼCD
	if(cdp) who["state"][cdp] = card["cd"];

	if(ok) {
		if(card["use_once"]) cards[n] = 0;	//����һ������Ʒ		
		msv1(card["msg_ok"], who, target, card);
	} else {
		msv1(card["msg_fail"], who, target, card);
	}
	return 0;
}

