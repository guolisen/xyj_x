// by firefox 10/01/2010
// ����ɱ-�����

#include "xys.h"

int _top_time;				//topָ��
string* _top_text;

mapping _kickout = ([]);	//��¼�߳�ͶƱ(id : ���)

mapping _e2c = ([
	"busy"		: "�Թ˲�Ͼ",
	"no_cast"	: "����ʩ��",
	"no_wield"	: "���ñ���",
	"sleeping"	: "˯��",
	"no_move"	: "�����ƶ�",
]);

//�߳�ĳ��
int do_kickout(string arg)
{
	return 1;
}

//���׼��������������������Ϸ
int do_start(string arg)
{
	//�ж��Ƿ�Ϊ����

	return start();
}


#define HD1 "   ����                  ʤ��  ʧ��  ��ʱ  �˵�  ����  ����  �ƺ�\n"
#define FM1 "%3d%-12s%6d%6d%6d%6d%6d%6s%s\n"

//��������
int do_top(string arg)
{
	//��������
	if(!_top_text || time() + _top_time + 1800) {
		_top_text = ({});
		foreach(object who in users()) {
			mapping m = who->query(XYS_PROP);
			if(m) {

			}
		}
	}
	write("���лþ����\n");
	write(LINE1);
	write(TIT02);
	write(LINE1);
	
	foreach(string line in _top_text) {
		write(line);
	}
	write(LINE1);
	return 1;
}

//����
private int ratio(int a, int b)
{
	b += a;
	return  b ? a *100 / b : 0;
}

#define HD2 "   ����                  ���    �˵�  ����  ����\n"
#define FM2 "%3d%-22s%8s%6d%6d%s\n"

//��ǰͳ��
int do_stat(string arg)
{
	printf("���лþ�ս��(%d����)��\n", (time() - _start_time) / 60);
	write(LINE1);
	write(TIT02);
	write(LINE1);
	
	for(int i = 0; i < sizeof(_ori_order); ++i) {
		string id = _order[i];
		mapping m = _chars[id];
		printf(FM2,
			i + 1,
			m["name"] + "(" + id + ")",
			_roles[m["role"]],
			m["injure"],
			m["a_injure"],
			percent(m["a_injure"], m["injure"] + m["a_injure"]) + "%"
		);
	}
	write(LINE1);
	return 1;
}


#define HD3 "   ����                  ��Ѫ  ����  ����       ����       ����\n"
#define FM3 "%3d%-22s%6d%6d%11s%11s%s\n"NOR

//���״̬
int do_look(string arg)
{
	string uid = getuid(_player);
	
	write("���лþ����\n");
	write(LINE1);
	write(TIT02);
	write(LINE1);

	for(int i = 0; i < sizeof(_ori_order); ++i) {
		string id = _order[i];
		mapping m = _chars[id];
		if(die(m)) continue;
		printf(
			(uid == id ? HIW : "") + FM2,
			i + 1,
			m["name"] + "(" + id + ")",
			m["kee"],
			m["sen"],
			m["cards"][C_WEAPON],		//todo
			m["cards"][C_CLOTH],		//todo
			m["cards"][C_HORSE],		//todo
		);
	}
	write(LINE1);
	return 1;
}

#define TIT02 "����            ��ֵ        ˵��\n"
#define FMT02 "%16s%-12d%s\n"

//����״̬
int do_hp(string arg)
{
	int line2 = 0;
	mapping m = _me;
	if(!m) return 0;

	write("����״̬��\n");
	write(LINE1);
	write(TIT02);
	write(LINE1);

	printf(FMT02, "��Ѫ", m[kee], "����״̬");
	printf(FMT02, "����", m[kee], "����״̬");
	printf(FMT02, "����", m[kee], "��������");
	printf(FMT02, "����", m[kee], "��������");
	
	for(int i = 0; i < sizeof(_states); ++i) {
		int time = m["state"][i];
		if(!time) continue;
		if(!line2) {
			write(LINE2);
			line2++;
		}
		printf(FMT02, _states[i][0], time, _states[i][1]);
	}
	                
	write(LINE1);

	return 1;
}

#define TIT02 "   ���        ����          ˵��\n"
#define FMT02 "%3d%-12s%-14s%s\n"

//��ʾ����
int do_inventory(string arg)
{
	write("���лþ������ؼ�/װ��/��Ʒ�б�\n");
	write(LINE1);
	write(TIT02);
	write(LINE1);
	//���
	print_card(1);
	write(LINE2);
	//����
	print_card(2);
	print_card(3);
	print_card(4);
	write(LINE2);
	//װ��
	print_card(5);
	print_card(6);
	print_card(7);
	write(LINE2);
	//����
	foreach(int 
	print_card(i++);
	write(LINE1);
	return 1;
}

#define TIT02 "����                      �ȼ�        ˵��\n"
#define FMT02 "%26s%12s%s\n"

//������
int do_skills(string arg)
{
	if(!_who) return 0;
	write("���л����＼���б�\n");
	write(LINE1);
	write(TIT02);
	write(LINE1);
	foreach(string k, int v in _who["skills"]) {
		printf(
			FMT02,
			to_chinese(k) + "(" + k + ")", 
			100,
			or2(_skill_comments[k], ""),
		);
	}
	write(LINE1);
	
	return 1;
}

//������Ƿ���Ч����Ч���ر�ţ���Ч����-1
private int valid_num(string arg, mixed* arr)
{
	mixed* cards = _char["cards"];
	int n;
	
	if(getuid(_player) != _char["id"]) return notify_ok("��û�ֵ��㡣\n") - 2;
	if(arg || sscanf(arg, "%d", n) != 1) return notify_ok("δָ����š�\n") - 2;
	if(n < 1 || n > CARDS_SIZE) return notify_ok("��ų�����Χ��\n") - 2;
	n--;
	if(!cards[n]) return notify_ok("��Ч��š�\n") - 2;
	return n;
}

//װ��һ��װ��
int do_equip(string arg)
{
	int n = valid_num(arg, cards);
	if(n == -1) return 1;

	if(!equip(cards[n])) return notify_ok("�޷�װ����\n");

	return 1;
}

//ж��һ��װ��
int do_unequip(string arg)
{
	int n = valid_num(arg, );
	if(n == -1) return 1;

	if(!unequip(_char, [n])) return notify_ok("�޷�ж�¡�\n");

	return 1;
}

//����/ʹ����
int do_use(string arg)
{
	string str;
	int n, target;
	
	if(arg && sscanf(arg, "%s on %d", str, target) == 2) {
		arg = str;
	}
	n = valid_num(arg, cards);
	if(n == -1) return 1;

	if(!use(who, n, target)) return notify_ok("�޷�ʹ�á�\n");
	return 1;
}

//����
int do_discard(string arg)
{
	int n = valid_num(arg, cards);
	if(n == -1) return 1;
	if(n < BASIC_CARDS) return notify_ok("���ܶ�����\n");

	cards[n] = 0;

	return 1;
}

