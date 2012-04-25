//��Ůɢ�� 

#include <ansi.h>
#include <xyj_x.h>

inherit SSERVER;

#define NAME	"��Ůɢ��"
#define CD		10
#define THR		80
#define MSG0	HIM"\n$N��ն������лû����������꣬����������£�\n"


int perform(object me, object target)
{	
	int skill = me->query_skill("baihua-zhang", 1);
	object* enemies = BTL->enemies(me);
	int power = me->query("force_factor");

	mapping req = ([
		"skill1"	: ([ "baihua-zhang" : 80 ]),
		"prop"		: ([ "force" : 25 + 4 * power, "mana" : 100 ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ DEXP : 1, "str" : -1 ]),
		"skill_pair": ([ ({"unarmed", "parry"}) : 3 ]),
		"state"		: ([ "busy" : 1 ]),
	]);

	if(!sizeof(enemies)) return notify_ok("��"NAME"��ֻ����ս����ʹ�á�\n");
	if(!BTL->require(me, NAME, req)) return 1;

	if(!cd_start(me, "im_pfm", CD)) return notify_fail("�����õ�̫��̫�ľͲ����ˡ�\n");
	BTL->pay(me, req["prop"]);

	msv(MSG0, me, target);

	foreach(object who in enemies) {
		if(BTL->cmp_random20(me, who, cmp_parm) > THR) {		
			int damage =  power / 2 - who->query_temp("apply/armor");		//��������Ч���ٰ������˺�������
			damage = max2(50, 4 * damage);
			trace("damage:" + damage);
			who->receive_damage("kee", damage);
			who->receive_wound("kee", damage);
			COMBAT_D->report_status(who, 1);
			BTL->fight_enemy(who, me);
		}
	}
	return 1;
}

