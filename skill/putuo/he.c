// firefox 04/12/2012
#include <ansi.h>
#include <xyj_x.h>

#define ID				"he"
#define NAME			HIY"����Ŧ"NOR
#define CD				10
#define DURATION		30

/*
������������֦����պ��һ���¶����ȥ���������ϣ���
ֻ��������ǹ��һ˫�ֺ��Ƶ��أ���Ҳ���ܿ��ţ���������һ������Ť��������Ҳ��
*/
#define MSG0			HIY"$N����$n����һ̧�֣��������ϣ���...\n"NOR
#define MSG1			HIY"$n����˫�ֺ��Ƶ��أ���Ҳ���ܿ��ţ�\n"NOR
#define MSG2			HIY"�·��й�����ץס$n������$n���ѡ�\n"NOR
#define MSG3			CYN"$N��һ������˫�����ڷֿ��ˡ�\n"NOR

int cmd_filter(object me, string verb, string arg)
{
	string* verbs = ({"perform", "wield", "get", "drop", "give"});
	if(member_array(verb, verbs) != -1) {
		write("��˫�ֲ��ܿ��ƣ�\n");
		return 1;
	}
	return 0;
}

int cast(object me, object target)
{
	int mana = 50 + me->query("mana_factor");
	mapping req = ([
		"skill1"	: ([ "buddhism"		: 120 ]),
		"prop"		: ([ "mana"			: mana ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ DEXP : 1, "mana_factor" : 1 ]),
		"skill"		: ([ "spells" : 3]),
		"temp"		: ([ "no_cast" : -1]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("��Ҫ��˭ʩ��"NAME"��");
	if(!BTL->require(me, NAME, req)) return 1;
	if(!cd_start(me, ID, CD)) return notify_fail("����ʱ������ʹ��"NAME"��\n");

	BTL->pay(me, req["prop"]);

	msv(MSG0, me, target);
	
	if(BTL->cmp_random20(me, target, cmp_parm) > 125) {
		object weapon, env = environment(target);
		while(weapon = me->query_temp("weapon")) {
			weapon->unequip();
			if(env) weapon->move(env);
		}
		BUFF->add(target, ([
			"id"		: ID,
			"name"		: NAME,
			"comment"	: "˫�ֺ��Ƶ��أ����ܿ��š�",
			"class"		: "������",
			"duration"	: DURATION,
			"add_temp"	: ([
				"no_attack"		: 1,
				"no_wield"		: 1,
				"cmd_filter/*"	: ({ (: cmd_filter :) }),
			]),
			"stop_msg"	: MSG3,
		]));
	} else {
		msv(MSG2, me, target);
	}
	BTL->fight_enemy(target, me);
	return 1;
}
