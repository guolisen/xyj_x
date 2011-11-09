//�������ơ� jinhun-zhang.c
//menpai skill

inherit SKILL;

mapping *action = ({
        ([      "action":
"$N����΢�֣�����һ��ʹ��һ�С�С����ծ����һֻ�Ұ׵���צ̽��$n��$l",
                "dodge":                15,
                "parry":                15,
                "force":                120,
                "damage_type":  "ץ��"
        ]),
        ([      "action":
"$Nٿ��һ��ת��˫��������һĨ���ֳ����������������ſ�һ����һ������ֱ��$n",
                "dodge":                -35,
                "parry":                -35,
                "force":                60,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N����΢б���漴���һ�������ֺ��ƺ�צʹ����Ⱥħ���衹������$n��$l",
                "dodge":                5,
                "parry":                5,
                "force":                80,
                "damage_type":  "����"
        ]),
        ([      "action":
"$Nʹ������Ӱ��������˫�ֻ����쳣��׼$n��$lץȥ",
                "dodge":                -5,
                "parry":                -10,
                "force":                80,
                "damage_type":  "ץ��"
        ]),
        ([      "action":
"$N������Σ�����ƮƮ�����ĳʱ��̣�һ�С���ع�������$n$l",
                "dodge":                15,
                "parry":                15,
                "force":                60,
                "damage_type":  "����"
        ]),
        ([      "action":
"$Nʹ����������·�������Ծ���䲻�������ǰ��׼$n$l�߳�һ��",
                "dodge":                -5,
                "parry":                -5,
                "force":                90,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N������$n$l���������һ�С����������צ����ͬһ��λץ��",
	    "dodge":                15,
                "parry":                15,
                "force":                70,
                "damage_type":  "ץ��"
        ]),
});

int valid_learn(object me)
{
	if( me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������Ʊ�����֡�\n");
	if( (int)me->query("max_force") < 50 )
		return notify_fail("�������̫�����޷��������ơ�\n");
	return 1;
}

int valid_enable(string usage) { return usage=="unarmed"; }

mapping query_action(object me, object weapon)
{
	int i;
	i=me->query("HellZhen");
	if( !me->query("HellZhen") ) {
		return action[random(sizeof(action))];
	} else {
		return action[i];
	}
}

int practice_skill(object me)
{
	if( (int)me->query("sen") < 40)
		return notify_fail("��ľ����޷������ˣ���Ϣһ�������ɡ�\n");
	if( (int)me->query("kee") < 40 )
		return notify_fail("����������������Ϣһ�������ɡ�\n");
	if( (int)me->query("force") < 10 )
		return notify_fail("������������ˡ�\n");

	me->receive_damage("kee", 40);
	me->receive_damage("sen", 40);
	me->add("force", -10);

	return 1;
}

#define at_night() (NATURE_D->query_current_day_phase() / 6)

mixed hit_ob(object me, object victim, int damage_bonus)
{	
	//���������Ҫ�أ������򶨣����ó󣬰�ҹ����
	int c1 = me->query("cor") + me->query("cps") - me->query("per");
	int c2 = victim->query("cor") + victim->query("cps") - victim->query("per");
	int ratio = c1 * 100 / max2(1, c2);
	int damage = victim->query("eff_sen") * min2(30, ratio) / 100;	//����˺�30%

	if(damage_bonus > 100 && at_night() && damage > 100) {
		if(cd_start(me, "unarmed_effect", 5))	{
			victim->receive_damage("sen", damage);
			victim->receive_wound("sen", damage / 3);
			return "�ڰ���$n���޷�������$N��һ�־���ͷƤ���飬��ë������\n";
		}
	}

	return 0;
}

