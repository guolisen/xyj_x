// mihun.c �Ի���
#include <ansi.h>

inherit SSERVER;

#define DURATION			30
#define NAME			"ʴ����"
#define MSG0			HIC"$N��ͷ�������˾����ģ���̧��ͷ����$n���ĵ�һЦ��\n"NOR
#define MSG1			HIR"$n������ؿ���$N������ϧ��֮����Ȼ���𣬾�Ȼ�����Լ���ս��֮�С�\n"NOR
#define MSG2			HIR"$n���ĵؿ���$Nһ�ۣ�����Ϊ������\n"NOR

int cast(object me, object target)
{
	int skill = me->query_skill("spells");
	mapping req = ([
		"skill1"	: ([ "moonshentong"	: 40 ]),
		"prop"		: ([ "mana"			: skill ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ DEXP : 1, "mana_factor" : 1 ]),
		"skill"		: ([ "spells" : 2]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("������˭�Ļꣿ");
	if(target->query_temp("no_move")) return notify_fail(target->name() + "�Ѿ��겻���ᣬ����ľ���ˣ�\n");  
	if(!BTL->require(me, NAME, req)) return 1;
	BTL->pay(me, req["prop"]);

	msv(MSG0, me, target);

	if(BTL->cmp_random20(me, target, cmp_parm) > 85) {
		msv(MSG1, me, target);


	} else {
		msv(MSG2, me, target);
		me->apply_condition(POISON, skill / 20);
		me->start_busy(1);
	}
	BTL->fight_enemy(target, me);
	return 3 + 2;
}

