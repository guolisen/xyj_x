// by firefox 11/21/2009

/*
�������������

- ������
- �������

�籾

ţħ�������ձ߸��������҆����Ҿ�ɱ�߸���
�׾���������҆��׹Ǳ�����

*/

#include <weapon.h>
#include <ansi.h>

inherit WHIP;

void create()
{
	set_name("�����", ({"whip"}));
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
	}
	init_whip(5);
	setup();
}

#define CD_ID				"bind"

void init_var()
{
	_subs = ([
		"���Ǳ�"			: ([
			"ids"			: ({"longgu bian", "bian", "whip"}),
			"long"			: "һ����ɭɭ�����ǣ�͸����������Ϣ��",
			"color"			: HIW,
			"unit"			: "��",
		]),
		"������"			: ([
			"ids"			: ({"ruanlong jin", "jin", "whip"}),
			"long"			: "һ��������͵����",
			"color"			: 0,
			"unit"			: "��",
		]),
	]);

	
	//����������/�ڹ���
	_trais = ([
		//��ʼ����
		"prop"	: ([			
			"personality"	: -1,
		]),

		//���ݰٷֱȼӳɵ�����
		"prop_x"	: ([
			"spells"		: 10,
			"damage"		: 40,
		]),
	]);

	_act = ([
		"exp_x"			: 50,					//50%�ľ���������������

		"cd_id"			: CD_ID,				//��CD��ID�����ַ������ܹ�CD
		"cd"			: 30,

		"target"		: ([ "need_enemy" : 1, "need_living" : 1 ]),

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
		"msg_start"		: "$N��������%s�ڿն�����$n��ȥ��",
		"msg_success"	: "%s��һ����������$n���˸����ʵʵ��",
		"msg_fail"		: "$n�߶������࿹��%s�������ַɻ�$N���С�",
	]);
}

//��������
int ji_success(object who, object target, int fabao_exp)
{
	//����


}
