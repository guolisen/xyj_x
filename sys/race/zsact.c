// by firefox 07/21/2010

#include <xyj_x.h>

/*

����

�ȼ���map unarmedһ�£�
�ܼ����׺ͼӳɣ�����dragonfight + ���У�������������yinfeng-zhua��

*/

void create()
{
	seteuid(getuid());
}


//��������
mapping _attack_act = ({
		
	//����
	"poison-tooth"		: ({
		"$N��Ӱ���ΰ㸽��$n���ϣ�¶��������"HIW"����"NOR"��������Ϣ����$nҧȥ��"
		"$NͻȻ������ɭɭ��"HIW"����"NOR"�ѵ���ǰ��$n����Ҫ��$N���вͣ�"
	}),

	//����ͷ
	"poison-tongue" : ({
		"$N����ͦ����˻˻ͻ��"HIR"����"NOR"��ֱ����$n��һ���ȷ����������",
	}),

	//����
	"snake-body"	: ({
		"$NѸ����ס$n���̶��������ϣ�Ҫ��$n��ס���ո�������ǡ�"
	}),

	"mouth"		: ({
		"$N�ſ�Ѫ���ڣ���ݺݵ���$nҧȥ��",
	}),

	"tail"		: ({
		"$N����һת��β����ֱ�һ����$nɨȥ��",
	});

	"horn"		: ({
		"$N�������ˣ�����ͦ�ǣ���۵糸����$nײȥ��",
		"$N����ͷ���ԽǶ�׼$n��һ������������$n��ȥ��",
		"$n�ص�$N�������������˭��$N��Ȼ��ͷ���ҽ������а������",
	}),

	//����
	"hoof"		: ({
		"$N����һԾ��ǰ�����������֮����$n̤�£�"
		"$N����һת������������$n��ȥ��"
	}),

	//è��/��/�׹Ǿ�
	"claw"	: ({
		"$NһԾ��������$n����צӭ��ץȥ��",
		"$N�ڿն�����צ�繳����$n��ͷץ�¡�"
	}),

	//��
	"palm"		: ({
		"$Nվ������������������$n�������¡�"
	}),

	//��
	"pincers"	: ({
		"$N�����ž���������ǯ����$n��ȥ��"
	})

	//�ǣ���


});

//�������ܣ��󲿷ַ��ˣ�������combatd
mapping _defense_act = ([

	"tail"		: ({
		"$n�ۼ�����������æ����Ӷ�β�ͣ�˳�ƽ�$N������",
	});

	"horn"		: ({
		"$n�Ѿ��޴��ɶ㣬æ��ͷת�ǣ���$N��ס��",
	}),

	"hoof"		: ({
		"$N����һ�������ڿգ����$n�Ĺ��ƣ�",
	}),

	"wing"		: ({
		"$Nɿ��˫�ᣬ������$n���ò��ջع��ơ�",
		"$Nһ�ɳ��죬$n�޳�Ī�������Ƶ�ʱ���⡣",
	}),

	"palm"		: ({
		"$N������ӭ��Ӳ������$n�𿪡�"
	}),

	"pincers"	: ({
		"$N�����񵲣�$n������������"
	})

	"shield"	: ({
		"$N�ƶ����Σ��Ժ����ԣ�$n�Ĺ����紥����ͭǽ����⽻��",
	}),

	"common"	: ({
		"$n�͵�һ����$N�Ĺ��Ƶ�����ա�",
		"$n�����ˣ�$N�޳�Ī����",
		"$n�ۼ��������ܲ��ã�$N�Ľ��������������޴�������",
	}),
]);


//��ȡ������Ϣ��Ŀǰû���ṩ������ص���Ϣ
string query_defense_msg()
{
	return random1(_defense_act["common"]) + "\n";
}

mapping _acts_tab = ([]);			//��������Ĺ�������

//��ȡ������Ϣ
string query_attack_act(object who)
{
	string race_id = RACE_D->query(who, id);
	mapping* acts = _acts_tab[race_id];

	if(!acts) {
		string* weapons = RACE_D->find(race_id)->query_weapons();
		string* msgs = ({});
		foreach(string weapon in weapons) {
			msgs += ({_attack_act[weapon]});
		}
		acts = ({});
		foreach(string msg in msgs) {
			mapping act = ([
				"action"		: msg + "\n",
				"force"			: 120,
				"dodge"			: -30,
				"parry"			: -60,			//����combatd�еĿ����м���ʧ
				"damage_type"	: "ץ��",
			]),
			acts += ({act});
		}
		_acts_tab[race_id] = acts;
	}
	return random1(acts);
}

//���и�������
mixed act_hit_ob(object me, object victim, int damage_bonus)
{
	if( damage_bonus < 100 ) return 0;

	if( random(damage_bonus/2) > victim->query_str() ) {
		victim->receive_wound("kee", (damage_bonus - 100) / 4 );
		return "��������������һ�����죬�����ǹ����������\n";
	}
}
