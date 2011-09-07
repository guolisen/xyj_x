// by firefox 11/21/2009

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"yinshen2"
#define NAME			HIW"����"NOR
#define DURATION		120
#define CD				20
#define PROP			"env/invisibility"

int cast(object me)
{
	mapping buff_ori = BUFF->find(me, ID);

	if(buff_ori) {									//�������
		BUFF->remove1(buff_ori);
		cd_start(me, ID, CD);
	}
	else if(cd_check(me, ID)) {						//����
		int skill = me->query_skill("buddhism", 1);
		int level = skill / 100;
		mapping req = ([
			"ex_value"	: ([ PROP				: "���Ѿ����������ˡ�" ]),
			"skill1"	: ([ "buddhism"			: 100 ]),
			"prop"		: ([ "mana"				: skill ]),
		]);
		mapping buff = ([
			"id"		: ID,
			"name"		: NAME,
			"comment"	: "��������״̬�����˿������㡣",
			"duration"	: DURATION,
			"temp"		: ([ "no_heal_up/yinshen" : 1 ]),
			"replace"	: ([ PROP				: max2(1, level) ]),

			"start_msg"	: "$N�૵����˼������\nֻ��һ��"HIW"�׹�"NOR"������$N�ټ����ޡ�\n",
			"stop_msg"	: "\n"HIW"�׹�"NOR"����֮��$N���ֳ������Ρ�\n",
		]);
		if(!BTL->require(me, NAME, req)) return 1;
		BTL->pay(me, req["prop"]);
		BUFF->add(me, buff);
	}
	return 1;
}
