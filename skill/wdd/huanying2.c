// by firefox 11/21/2009

inherit SSERVER;
inherit "/d/sldh2/feature/util.c";
inherit "/d/sldh2/feature/buff";

#include <ansi.h>

#define BUFF_ID			"huanying2"
#define BUFF_NAME		"��Ӱ"

int cast(object me, object target)
{
	int skill = me->query_skill("yaofa", 1);
	mapping req = ([
		"ex_temp"	: ([ "yinshen_busy"		: "�������޷�ʩչ��Ӱ��"]),
		"ex_value"	: ([ "env/invisibility"	: "�������޷�ʩչ��Ӱ��"]),
		"skill1"	: ([ "yaofa"		: 250]),
		"value"		: ([ "mana"			: 100]),
	]);
	mapping buff = ([
		"id"		: BUFF_ID,
		"name"		: BUFF_NAME,
		"comment"	: "���ڻ�Ӱ״̬��",
		"duration"	: 10,
		"temp"		: ([
			"no_heal_up/yinshen" : 1,
			"yinshen_busy"	: 1,
		]),
		"replace"	: ([ "env/invisibility"	: 1 ]),
		"stop_msg"	: "����ɢ��������������$N�����Ρ�\n",
		"post_act"	: function(object target, mapping buff) {

		},
	]);
	if(query_cd(me, BUFF_ID)) return fail_msg("�㻹����ʩ�Ż�Ӱ��\n");
	if(!require(me, BUFF_NAME, req)) return 1;
	pay(me, req["value"]);
	printf("�����Ĭ�����ģ����һ�����̡�˲��һ����Ӱ������������ǰ���������������١�\n");

	//������������������
	if(!require(me, BUFF_NAME, req)) return 1;
	pay(me, req["value"]);
	add_buff(me, buff);
	buff_start_cd(me, buff, 15);

	//������
	me->remove_all_killer();
	foreach(object who in all_inventory(environment(me))) {
		if(living(who)) who->remove_killer(me);
	}

	//��Ӱ������
	{
		object obj = new("/d/sldh2/feature/hufa");
		obj->move(environment(me));
		obj->invocation(me);
		obj->set_temp("invoker", me);
	}
	return 1;

}
