// firefox 11/21/2009

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define ID			"wuxue"
#define NAME		HIW"��ѩ"NOR
#define DURATION	60
#define CD			70

int perform(object me, object target)
{
	mapping buff_ori = BUFF->find(me, ID);	

	if(buff_ori) {
		BUFF->remove1(buff_ori);
	} 	
	else if(cd_check(me, ID)) {
		int enhance = me->query_skill("dodge") * 40 / (20 + me->query("str"));	//�����سɷ���
		mapping req = ([
			"ex_temp"	: ([ "powerup"		: "���Ѿ����˹����ˡ�" ]),
			"skill_map"	: ([ "dodge"		: "moondance",	"force"		: "moonforce" ]),
			"skill"		: ([ "dodge"		: 100,			"sword"		: 100,		 "force"	: 100 ]),
			"prop"		: ([ "force"		: 50 ]),
		]);
		mapping buff = ([
			"id"		: ID,
			"name"		: NAME,
			"comment"	: "ʩչ��ѩ���Ṧ��ߡ�",
			"duration"	: DURATION,
			"temp"		: ([ "powerup" : 1 ]),
			"add_apply"	: ([
				"attack"	: -enhance,
				"dodge"		: enhance,
			]),
			"start_msg"	: HIW"$N��һ�����������Ṧ���ν����衣ֻ��$N�㲻մ�أ����н�Խ��Խ�죬�𽥻���һ�Ű������ù�����",
			"stop_msg"	: HIW"$N�����Ų����Ż����С�",
		]);
		if(!BTL->require(me, NAME, req)) return 1;
		if(!cd_start(me, ID, CD)) return notify_fail("����ʱ������ʹ��"NAME"��\n");
		BTL->pay(me, req["prop"]);
		BUFF->add(me, buff);
	}
	return 1;
}
