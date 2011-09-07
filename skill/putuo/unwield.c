// by firefox  06/22/2009

inherit F_CLEAN_UP;

#include <ansi.h>
#include <xyj_x.h>

#define ID				"unwield"
#define NAME			HIY"��������"NOR
#define DURATION		30
#define CD				10

#define MSG0				"�Է��Ѿ����������ˡ�"

int cast(object me, object target)
{
	int skill = me->query_skill("buddhism", 1);
	mapping req = ([
		"cd"		: ([ ID			: 1 ]),
		"ex_temp"	: ([ "No_Wield"	: MSG0]),
		"skill1"	: ([ "buddhism"	: 250 ]),
		"prop"		: ([ "mana"		: skill ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ "mana"		: 2,	"daoxing"	: 2 ]),
		"skill"		: ([ "spells"	: 4 ]),
	]);
	
	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("ҪȰ˭����������");
	if(!target->query_temp("weapon")) return notify_ok(MSG0 + "\n");
	if(!BTL->require(me, NAME, req)) return 1;
	BTL->pay(me, req["prop"]);
	BUFF->start_cd(me, ID, NAME, CD);

	message_vision(
		"ͻȻ������������ǧ����$N��Ŀ��ʮ�����������\n\n"HIY
		"    �ຣ�ޱߣ���ͷ�ǰ����������������سɷ�\n\n" NOR, me);

	if(BTL->random_pct(BTL->cmp_parm(me, target, cmp_parm), 30) >= 40) {
		BUFF->start_no_wield(me, DURATION, HIY"$N���ķ�⽥����ȥ��\n");
		BUFF->start_no_wield(target, DURATION);
		message_vision("$N��֪�������أ��پ����б�������ǧ���أ���Ҳ�ٲ�������\n\n", target);
	} else {
		message_vision("$n��$N�Ļ�������ţ���Ϊ������\n\n", me, target);
	}
	me->start_busy(1);

	return 1;
}
