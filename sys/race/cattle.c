// by firefox 06/21/2010

#include "race-base.h"

string _long = @LONG

һͷţ��ͷ����룬�������⣬��ֻ���������������������С�
��ͷ��β����ǧ���ɳ��̣������������а˰��ɸ��¡�

LONG;

void init_var()
{
	//���������Լ�����
	_subs = ([
		"��ţ"			: ([
			"ids"			: ({"bai niu", "niu", "cattle"}),
			"long"			: _long,
			"color"			: HIW,
			"unit"			: "ͷ",
		]),
		"��ţ"			: ([
			"ids"			: ({"qing niu", "niu", "cattle"}),
			"long"			: _long,
			"color"			: HIC,
			"unit"			: "ͷ",
		]),
	]);

	//��������
	_traits = ([
		"limbs"			: CATTLE_LIMBS,

		"kee"			: 400,					//��Ѫ����
		"sen"			: 0,					//��������

		//ֱ�Ӽӳ�����
		"add_apply"		: ([
			"personality"	: -30,
		]),
		
		//���ٷֱȼӳɵ�����
		"add_apply_x"		: ([
			"armor"			: 100,
			"strength"		: 30,
			"parry"			: 0,				//�����мܰ�
			"dodge"			: 0,				//����̫������ת��Ų
		]),

		"skill_bonus"	: ([					//���ܼӳɣ����ջ����ӵ�apply��
			"moyun-shou"	: 10,
			"moshenbu"		: 10,
			"huomoforce"	: 10,
			"pingtian-dafa"	: 20,
		]),
	]);
	
	//����
	_weapons = ({ "horn", "hoof", "tail"});

	//������Ϣ
	_born = ([
		"place"		: "/d/gao/daotian1",
		"sb."		: "/d/gao/npc/bull",
		"msg"		: "$N��ͨһ�����ڵ��ϣ����˹�����\n" + CYN + MSG_LICK,
	]);
}


#define CURE_RATIO		300

mapping _act_tab = ([
	"hand"		: "��",			"axe"		: "��",
	"blade"		: "��",			"sword"		: "��",
	"dagger"	: "��",			"fork"		: "��",
	"hammer"	: "��",			"spear"		: "��",
	"staff"		: "ɨ",			"stick"		: "ɨ",
	"throwing"	: "��",			"whip"		: "��",
	"mace"		: "��",
]);

string _msg = CYN"\n$n���һ����$N��ͷ%s��������\n"
	+ "$Nǻ�������һ��ţͷ�������º������۷Ž�⣡\n"NOR;

//ʩչ����
int unique_skill(object me, object target)
{
	int eff_kee = me->query("eff_kee");
	int max_kee = me->query("max_kee");
	int cure = me->query_skill("spells") * CURE_RATIO / 100;
	
	if(eff_kee > max_kee/3) return notify_fail("û�˴����ͷ������������\n");
	else {
		object enemy = BTL->random_enemy(me);
		object weapon = enemy->query_temp("weapon");
		string act = "��";
		if(weapon) act = or2(_act_tab[weapon->query("skill_type")], act);

		MSG->vision(_msg, me, enemy, act);

		me->add("mana", cure/10);
		me->receive_curing("kee", cure);
		me->receive_heal("kee", cure);
		new("/d/qujing/jilei/obj/head")->move(environment(me));
	}
	return 0;
}

