
inherit SSERVER;
#include <ansi.h>
#include <xyj_x.h>

#define POISON			"moon_poison"
#define NAME			"ʴ����"
#define MSG0			HIC"$N��ͷĬĬ�������ģ����н�������һ�Ź���ѩ�׵������ƺ��������͵Ĺ�â��\n"NOR
#define MSG1			HIR"$n����$N����̬֮���������ɷ������һ����ȴ�����ǹ���һ����ͻȻ����$n��\n"NOR
#define MSG2			HIR"$N��ɫ�԰ף��ƺ�������֧�����������н�����ȥ����\n"NOR

int cast(object me, object target)
{
	int skill = me->query_skill("spells");
	mapping req = ([
		"skill1"	: ([ "moonshentong"	: 60 ]),
		"prop"		: ([ "mana"			: skill ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ DEXP : 1, "mana_factor" : 1 ]),
		"skill"		: ([ "spells" : 2]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("�����˭ʩչʴ���䣿\n");
	if(target->query_condition(POISON)) return notify_fail(target->name() + "�Ѿ���а�ˣ�\n");  
	if(!BTL->require(me, NAME, req)) return 1;
	BTL->pay(me, req["prop"]);

	msv(MSG0, me, target);

	if(BTL->cmp_random20(me, target, cmp_parm) > 85) {
		int damage =  skill / 2;
		msv(MSG1, me, target);
		trace("damage:" + damage);
		target->apply_condition(POISON, skill / 5);
		target->receive_damage("sen", damage, me);
		target->receive_damage("kee", damage);
		target->receive_wound("sen", damage);
		target->receive_wound("kee", damage);

		me->start_busy(1);
	} else {
		msv(MSG2, me, target);
		me->apply_condition(POISON, skill / 10);
	}
	BTL->fight_enemy(target, me);
	return 2;
}

