// by firefox & shines 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>

#define BUFF_ID			"zhenshen2"
#define BUFF_NAME		"����"

#define DURATION		120		//���ܳ���ʱ��
#define CD				5		//������ȴʱ��


mapping query_trait(object who);
int on_timer(mapping buff);

int exert(object me, object target)
{
	mapping buff_ori = BUFF->find(me, BUFF_ID);

	if(buff_ori) {									//�������
		BUFF->remove(buff_ori);
	} else {										//����
		int skill = me->query_skill("dragonforce", 1);
		int kee_gain = skill * 4;
		mapping req = ([
			"cd"		: ([ BUFF_ID	: 1 ]),
			"ex_temp"	: ([ "no_wield" : 1, "powerup" : 1, "d_mana" : 1]),
			"ex_class"	: ([ "������" : 1 ]),
			"skill1"	: ([ "dragonforce"	: 250]),
			"prop"		: ([ "force"		: 300,	"kee"		: 150,	"sen"		: 150]),
		]);
		mapping trait = query_trait(me);
		
		mapping buff = ([
			"id"		: BUFF_ID,
			"name"		: BUFF_NAME,
			"comment"	: "�����һ������ӵ��������ǿ������ǿ��������",
			"class"		: "������",
			"duration"	: DURATION,
			"temp"		: ([
				"apply/name"	: ({ trait["name"] }),
				"apply/id"		: ({ trait["id"] }),
				"apply/short"	: ({ trait["short"] }),
				"apply/long"	: ({ trait["long"] + NOR"\n" }),
				"no_wield"		: 1,
				"powerup"		: 1,
			]),
			"add_apply"	: ([
				"armor"		: skill / 2,		//TODO:״̬��ǿ����
				"unarmed"	: skill / 2,
				"parry"		: skill,			//�첲�֣����мܣ�combatd�п����гͷ�
				"force"		: skill * 2,		//���roar
				"dodge"		: -skill / 2,		//����̫������ת��Ų
				"personality"	: -30,			//���Ƚ�����
			]),
			"replace"	: ([
				"limbs"		: ({ "ͷ��", "����", "ǰצ", "β��", "��Ƥ", "��צ"}),
				"force_factor" : (int)me->query_skill("force") / 2 + skill,
			]),
			"add"		: ([
				"max_kee"		: kee_gain,
				"kee"			: kee_gain,
			]),
			"start_msg"	: HIC"$N�������������һ����Ѫ��֮������Ϊһ��������צ��"
				+ trait["name"] + HIC"���˵�ɱ�����ˡ�",
			"stop_msg"	: HIC"$N�������ķ�����һ������ϣ�����Ҳ������ԭ�ˡ�",
			"post_act"	: function(mapping buff) {
				object me = buff["me"];
				me->receive_curing("kee", 1);
				me->receive_heal("kee", 1);
			},
			"interval"	: 4,
			"timer_act"	: (: on_timer :),	
		]);

		if(!BTL->require(me, BUFF_NAME, req)) return 1;
		BTL->pay(me, (["force" : skill]));
		BUFF->add(me, buff);
		BUFF->start_cd2(me, buff, CD);

		me->receive_curing("kee", kee_gain);
		me->start_busy(1);
	}
	return 1;
}

//��ʱ����������Ч
int on_timer(mapping buff)
{
		/*object enemy = query_temp("last_damage_from");
	object weapon;
	if(enemy && weapon = enemy->query_temp("weapon")) {
		damage = weapon->query("weapon_prop/damage");
	}
	//�����ڻ���$N�������·�Ҫ��$n���ϵĻ����ڻ�/������set("material", "steel");
	//query("material") != "ice" ) "bone");*/

	return 1;
}

//��ȡ��������������
mapping query_trait(object who)
{
	mapping trait = ([
		"seashentong"	: ([
			"name"			: "����",
			"long"			: "һ�����������Ƴ��ߡ������ס�����β�����г��롢������¹������צ��",
			"color"			: HIC,
			"act_prob"		: 50,
			"act"			: function(object target, mapping buff) {
				//�˺���
			},
		]),
		"taiyi"	: ([
			"name"			: "����",
			"long"			: "һ��������ȫ���л���ơ�",
			"color"			: HIR,
			"act_prob"		: 50,
			"act"			: function(object target, mapping buff) {
			},
		]),
		"gouhunshu"		: ([
			"name"			: "���",
			"long"			: "һ����������ɣ����ɫ���������ġ�",
			"color"			: HIB,
			"act_prob"		: 50,
			"act"			: function(object target, mapping buff) {
				//�ж�
			},
		]),
		"dengxian-dafa"	: ([
			"name"			: "����",
			"long"			: "һ���������������ˡ�",
			"color"			: HIW,
			"act_prob"		: 50,
			"act"			: function(object target, mapping buff) {
				//no_move
			},
		]),
		"misc"	: ([
			"name"			: "����",
			"long"			: "һ��������״���ߣ����绢������ţ�������ɡ�",
			"color"			: HIG,
			"act_prob"		: 50,
			"act"			: function(object target, mapping buff) {
				//
			},
		]),
	]);
	mapping m;
	string spells = who->query_skill_mapped("spells");
	if(!spells || !trait[spells]) spells = "misc";
	if(spells == "pingtian-dafa") spells = "taiyi";

	m = trait[spells];
	if(!m["id"]) m["id"] = "dragon";
	if(!m["short"])
		m["short"] = m["color"] + m["name"] + NOR + "(Dragon)";
	return m;
}
