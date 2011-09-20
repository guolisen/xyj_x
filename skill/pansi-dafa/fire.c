// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <ansi.h>
#include <xyj_x.h>

#define ID				"sm-fire"
#define NAME			HIB"�����׹ǻ�"NOR
#define CD				10
#define DURATION		4

#define MSG0			"$N������$nһָ����㲻�ײ����"HIB"�׹�"NOR"��$n��������...\n"NOR
#define MSG1			HIY"$n��%sͻȻ��𣬾���ʧ�룬ƴ���˴�\n"NOR
#define MSG2			"$nһ����"HIB"�׹�"NOR"���Ʈɢ��...\n"NOR
#define MSG3			CYN"$N�����˰׹ǻ𣬵�%s�Ѿ�һƬ���ڡ�\n"

/*
�׾����������Ҳ��������׹ǻ����ǲ�����ϵģ�(����һָ�����𱦵����������)
���𱦣����õ��������գ��ο��أ������α��أ�����
�׾������ѵ��Ҹ���ˣ�(������ǰ��������) 
*/

void po_lost(object target, int n);

int cast(object me, object target)
{
	int mana = 10 + me->query("mana_factor");
	mapping req = ([
		"cd"		: ([ ID				: 1 ]),
		"skill1"	: ([ "pansi-dafa"	: 20 ]),
		"prop"		: ([ "mana"			: mana ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ DEXP : 1, "mana_factor" : 1, "sen" : 1, "max_sen" : -1 ]),
		"skill"		: ([ "spells" : 3]),
		"temp"		: ([ "no_cast" : -1]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("��Ҫ��˭��");
	if(!BTL->require(me, NAME, req)) return 1;

	BTL->pay(me, req["prop"]);
	BUFF->start_cd(me, ID, NAME, CD);

	msv(MSG0, me, target);

	if(BTL->cmp_random20(me, target, cmp_parm) > 75) {
		int damage = 50 + mana * 2;
		string part = (target->query("gender") == "Ů��") ? "����" : random1(({"����", "�ɲ�"}));
		if(target->query_temp("weapon"))
			BUFF->start_no_wield(target, DURATION, sprintf(MSG3, part));
		msvx(MSG1, me, target, part);

		target->receive_damage("kee", damage, me);
		target->receive_wound("kee", damage, me);

		if(!userp(target) && !random(10)) {
			target->command("say ���õ��������գ��ο��أ������α��أ�����");
		}
		
		SKILL_D("pansi-dafa")->random_level_up(me);

	} else {
		msv(MSG2, me, target);
	}
	BTL->fight_enemy(target, me);
	return 2;
}
