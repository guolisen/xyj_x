// by firefox 11/21/2009

//�ؼ�����棬һǹ��ĳĳ��������


#include <ansi.h>

void create()
{
	set_name("��", ({"horse"}));
	set("race", "Ұ��");
	set("age", 10);
	set("combat_exp", 10000);
	set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
	set("verbs", ({ "bite"}));

	set("ride/msg", "��");
	set("ride/dodge", 20);
}

#define DESC			"һƥ�񿥵�ǧ����"
#define DESC8			"һƥ���������˿�֮һ��"
#define DESC9			"һƥ�����ĵ۾���֮һ��"
#define DESC_LEE		"��������Ԫ�Ե�����������ţ����Ժ�����"

void init_var()
{
	_subs = ([

		"����͸����"	: ([
			"ids"			: ({"yellow dragon", "dragon", "horse"}),
			"long"			: "һƥ���½ý���ս��ͨ��Ȼƣ�ë����ɫ��",
			"color"			: HIY,
		]),
		"ǧ��һյ��"	: ([
			"ids"			: ({"red lamp", "lamp", "horse"}),
			"long"			: DESC_LEE,
			"color"			: HIR,
		]),
		"����������"	: ([
			"ids"			: ({"red lamp", "lamp", "horse"}),
			"long"			: DESC_LEE,
		]),
		"������߾�"	: ([
			"ids"			: ({"spot horse", "horse"}),
			"long"			: "һƥ����ߵ�Ŀ���",
			"color"			: HIC,
		]),
		"û�������"	: ([
			"ids"			: ({"scabies kirin", "kirin", "horse"}),
			"long"			: "һƥ������Ŀ���",
			"color"			: HIB,
		]),
		"̤�ڰ�ѩ��"			: ([
			"ids"			: ({"snow horse", "horse"}),
			"long"			: "һƥͨ��ѩ�׵Ŀ���",
			"color"			: HIW,
		]),
		"��̿������"			: ([
			"ids"			: ({"fire horse", "horse"}),
			"long"			: "һƥͨ����Ŀ���",
			"color"			: HIR,
		]),
		"����"			: ([
			"ids"			: ({"jinjing shou", "shou", "horse"}),
			"long"			: "һƥ��¶���Ŀ���" ,
			"color"			: HIY,
		]),


		"����"			: ([
			"ids"			: ({"hua liu", "horse"}),
			"long"			: "ɫ�绪���࣬�����˿�֮һ��",
			"color"			: RED,
		]),
		"����"			: ([
			"ids"			: ({"qi ji", "horse"}),
			"long"			: DESC,
		]),
		"�̶�"			: ([
			"ids"			: ({"lu er", "horse"}),
			"long"			: DESC8,
		]),
		"����"			: ([
			"ids"			: ({"xian li", "horse"}),
			"long"			: DESC,
		]),

		"��ý��"			: ([
			"ids"			: ({"longmei jun", "jun", "horse"}),
			"long"			: DESC,
		]),
		"������"			: ([
			"ids"			: ({"ziyan liu", "liu", "horse"}),
			"long"			: DESC9,
			"color"			: MAG,
		]),
		"Ю��"			: ([
			"ids"			: ({"xie yi", "horse"}),
			"long"			: "����˫�����������ܰ�����ݣ������˿�֮ĩ��",
		]),
		"�X�Z"			: ([
			"ids"			: ({"su shuang", "horse"}),
			"long"			: DESC,
			"color"			: WHT,
		]),

		
		"�i�f��"			: ([
			"ids"			: ({"jue ti", "horse"}),
			"long"			: "����֮�ӣ�ǧ���i�f���뺹Ѫ����������",
		]),
		"���Z"			: ([
			"ids"			: ({"yin ge", "horse"}),
			"long"			: DESC,
			"color"			: WHT,
		]),
		"�[љ"			: ([
			"ids"			: ({"yao niao", "horse"}),
			"long"			: DESC,
		]),
		"�ɻ�"			: ([
			"ids"			: ({"fei huang", "horse"}),
			"long"			: DESC,
		]),

		
		"�P�B"			: ([
			"ids"			: ({"tao tu", "horse"}),
			"long"			: "�����ޡ���춱�������״����ɫ�ࡣ��",
			"color"			: HIC,
		]),
		"����"			: ([
			"ids"			: ({"fan yu", "horse"}),
			"long"			: "��������裬�����˿�֮һ��",
		]),
		"����"			: ([
			"ids"			: ({"chi tu", "horse"}),
			"long"			: "����һƥ������ǧ���ˮ��ɽ������ƽ�ء�",
			"color"			: RED,
		]),
		"����"			: ([
			"ids"			: ({"chao guang", "horse"}),
			"long"			: DESC8,
		]),

		
		"���"			: ([
			"ids"			: ({"yu hui", "horse"}),
			"long"			: DESC8,
		]),
		"�־�"			: ([
			"ids"			: ({"mi jing", "horse"}),
			"long"			: DESC,
		]),
		"����"			: ([
			"ids"			: ({"teng wu", "horse"}),
			"long"			: DESC8,
		]),
		"ʤ��"			: ([
			"ids"			: ({"sheng huang", "horse"}),
			"long"			: "��˵�е���ԡ���״��������������ǡ�",
			"color"			: YEL,
		]),

		"׷��"			: ([
			"ids"			: ({"zhui feng", "horse"}),
			"long"			: DESC,
		]),
		"����"			: ([
			"ids"			: ({"jue di", "horse"}),
			"long"			: DESC,
		]),
		"�ɷ�"			: ([
			"ids"			: ({"fan fei", "horse"}),
			"long"			: DESC,
		]),
		"����"			: ([
			"ids"			: ({"ben xiao", "horse"}),
			"long"			: DESC8,
		]),

		"��Ʈ"			: ([
			"ids"			: ({"yi piao", "horse"}),
			"long"			: DESC,
		]),
		"���"			: ([
			"ids"			: ({"chi dian", "horse"}),
			"long"			: DESC9,
			"color"			: HIR,
		]),
		"ͭ��"			: ([
			"ids"			: ({"tong jue", "horse"}),
			"long"			: DESC,
			"color"			: YEL,
		]),
		"����"			: ([
			"ids"			: ({"fu yun", "horse"}),
			"long"			: DESC9,
			"color"			: WHT,
		]),

		"����"			: ([
			"ids"			: ({"cong long", "horse"}),
			"long"			: "һƥ����ëɫ������ӣ������ຣ������Ҳ��",
		]),
		"����"			: ([
			"ids"			: ({"hu ci", "horse"}),
			"long"			: DESC,
		]),
		"����"			: ([
			"ids"			: ({"jue chen", "horse"}),
			"long"			: DESC9,
		]),
		"����"			: ([
			"ids"			: ({"zi lin", "horse"}),
			"long"			: DESC8,
			"color"			: MAG,
		]),

		"��Ⱥ"			: ([
			"ids"			: ({"jue qun", "horse"}),
			"long"			: DESC9,
		]),
		"��Ⱥ"			: ([
			"ids"			: ({"yi qun", "horse"}),
			"long"			: DESC9,
		]),
		"»���"			: ([
			"ids"			: ({"luli cong", "horse"}),
			"long"			: DESC9,
		]),
		"����"			: ([
			"ids"			: ({"ling zi", "horse"}),
			"long"			: DESC9,
		]),
		"�׾�"			: ([
			"ids"			: ({"lin ju", "horse"}),
			"long"			: DESC9,
		]),

	]);
	
	//����������ֻ�ܼ�dodge
	_traits = ([
		//��ʼ����
		"prop"	: ([
			"dodge"	: 1,
		]),

		//���ٷֱȼӳɵ�����
		"prop_x"	: ([
			"dodge"			: 100,
		]),

		"come_msg"	: "һ����˻��$n�ӹ����̳��м��۶�����",
		"leave_msg"	: "һ����˻��$n������ȥ��",
	]);
}


