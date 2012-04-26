// by firefox 11/21/2009

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"lianhua"
#define NAME			HIW"��������"NOR
#define CD				30
#define DURATION		19

int on_timer(mapping buff);

int cast(object me)
{
	int skill = me->query_skill("buddhism", 1);
	int interval = (1 + me->query("betray/count")) * 5;
	mapping req = ([
		"ex_temp"	: ([ "anti_magic"	: "���Ѿ����˹����ˡ�"]),
		"skill1"	: ([ "buddhism"		: 50]),
		"prop"		: ([ "mana"			: skill ]),
	]);
	mapping buff = ([
		"id"		: ID,
		"name"		: NAME,
		"comment"	: "ʥ������������㡣",
		"duration"	: DURATION,
		"temp"		: ([ "anti_magic"	: skill * 2]),
		"interval"	: interval,
		"timer_act"	: (: on_timer :),
		"start_msg"	: HIC"$N΢һ���񣬱���ó�һ���������ɫ�������֡�",
		"stop_msg"	: HIC"$N���İ���������ȥ�ˡ�",
		"_skill"	: skill,
	]);
	if(!BTL->require(me, NAME, req)) return 1;
	if(!cd_start(me, ID, CD)) return notify_fail("����ʱ������ʹ��"NAME"��\n");

	BTL->pay(me, req["prop"]);
	BUFF->add(me, buff);

	return 1;
}

int on_timer(mapping buff)
{
	object me = buff["me"];
	int skill = buff["_skill"];

	if(me->query_temp("no_cast")) me->delete_temp("no_cast");
	HP->add_mana(me, skill * 2);
	return 1;
}
