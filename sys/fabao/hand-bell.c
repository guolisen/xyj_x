// by firefox 11/21/2009

/*
������������

- ����
- ��������

�籾

��ϼ��������������꯺��Ĵ��������裬Ȼ�����ѡ�

*/
#include <armor.h>
#include "_base.h"

inherit HANDS;

void create()
{
	set_name("����", ({"hand bell"}));
	set_weight(80);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("material", "steel");
	}
	setup();
}

#define CD_ID				"dance"

void init_var()
{
	_subs = ([
		"��������"			: ([
			"ids"			: ({"yinsuo jinling", "jinling", "ling", "bell"}),
			"long"			: "һ�������ߴ���Ľ��ᡣ",
			"color"			: HIY,
			"unit"			: "��",
		]),
		"��������"			: ([
			"ids"			: ({"jinsuo yinling", "yinling", "ling", "bell"}),
			"long"			: "һ���ý��ߴ�������ᡣ",
			"color"			: WHT,
			"unit"			: "��",
		]),
	]);

	
	//����������/�ڹ���
	_trais = ([
		//����
		"prop"	: ([			
			"personality"	: 1,
		]),

		//���ٷֱȼӳɵ�����
		"prop_x"	: ([
			"armor"			: 10,
			"spells"		: 50,
		]),

		"prop_x"	: ([
			"damage"		: 10,		//1M 5�㣿
		]),

		"eff_x"			: 50,	//��Ч��ռ����
		
		"on_wound"		: (: on_wound :),

	]);

	_act = ([
		"exp_x"			: 50,					//50%�ľ�����������

		"cd_id"			: CD_ID,				//��CD��ID�����ַ������ܹ�CD
		"cd"			: 30,

		"target"		: ([ "need_enemies" : 1, "need_living" : 1 ]),

		"req"			: ([
			"cd"			: ([ CD_ID			: 1 ]),
			"skill1"		: ([ "spells"		: 100]),
			"prop"			: ([ "mana"			: 100,	"sen"	: 20 ]),
		]),
		"cmp"			: ([
			"prop"			: ([ "sen" : 1, "max_sen" : -1, "mana_factor" : 1, DEXP : 1 ]),
			"temp"			: ([ "no_cast" : -2 ]),
			"skill"			: ([ "spells" : 2]),
		]),
		"threshold"		: 60,
		"msg_start"		: "$Nҡ�����ϵ�%s������ö�����������������",
		"msg_success"	: "$n��������Ⱦ��Ц���տ������������ظ����衣",
		"msg_fail"		: 0,
	]);
}

//�ܵ��˺�
void on_wound(object owner, object attacker)
{
}

//��������
int ji_success(object who, object target, int fabao_exp)
{
	//���ܳ��У����ܶ�������kill���ܵ����ѹ���


}
