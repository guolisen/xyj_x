// by firefox 11/21/2009

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define BUFF_ID		"wuxue2"
#define BUFF_NAME	HIW"��ѩ"NOR
#define DURATION	60
#define CD			10

int perform(object me, object target)
{
	mapping buff_ori = BUFF->find(me, BUFF_ID);

	if(buff_ori) {
		BUFF->remove1(buff_ori);
		cd_start(me, BUFF_ID, CD);
	} 	
	else if(cd_check(me, BUFF_ID)) {
		mapping req = ([
			"cd"		: ([ BUFF_ID : 1 ]),
			"ex_temp"	: ([ "powerup"		: "���Ѿ����˹����ˡ�" ]),
			"skill_map"	: ([ "dodge"		: "moondance",	"force"		: "moonforce" ]),
			"skill"		: ([ "dodge"		: 100,			"sword"		: 100,		 "force"	: 100 ]),
			"prop"		: ([ "force"		: 50 ]),
		]);
		mapping buff = ([
			"id"		: BUFF_ID,
			"name"		: BUFF_NAME,
			"comment"	: "ʩչ��ѩ���Ṧ��ߡ�",
			"duration"	: DURATION,
			"temp"		: ([ "powerup" : 1 ]),
			"add_apply"	: ([
				"attack"	: -me->query_skill("sword"),
				"dodge"		: me->query_skill("dodge") * 2,
			]),
			"start_msg"	: HIW"$N��һ�����������Ṧ���ν����衣ֻ��$N�㲻մ�أ����н�Խ��Խ�죬�𽥻���һ�Ű������ù�����",
			"stop_msg"	: HIW"$N�����Ų����Ż����С�",
		]);
		if(!BTL->require(me, BUFF_NAME, req)) return 1;
		BTL->pay(me, req["prop"]);
		BUFF->add(me, buff);
	}
	return 1;
}
