// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"love"
#define NAME			HIM"�����"NOR
#define CD				20
#define DURATION		4

void tired(object who, int str);

int cast(object me, object target)
{
	int skill = me->query_skill("spells");
	mapping req = ([
		"cd"		: ([ ID			: 1 ]),
		"skill1"	: ([ "spells"	: 50 ]),
		"prop"		: ([ "mana"		: skill/2 ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ "per" : 3, "cps" : 3, "str" : -3, DEXP : 1, "max_mana" : 3 ]),
		"skill"		: ([ "spells" : 3]),
		"temp"		: ([ "no_cast" : -1]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("����˭��\n");
	if(me->query_per() < 20) return notify_ok("��̫���ˣ���ȥ�����ˡ�\n");
	if(BUFF->find(target, ID)) return notify_ok("�Է��Ѿ����Ե��ˣ�\n");
	if(!BTL->require(me, NAME, req)) return 1;

	BTL->pay(me, req["prop"]);
	
	BUFF->start_cd(me, ID, NAME, CD);

	msv(HIM"\n$N���������$n�������ﲨĿ�����룬���������...\n"NOR, me, target);

	if(BTL->cmp_random20(me, target, cmp_parm) > 80) {
		int force = target->query("force");
		target->add("force", max2(-force, -skill * 4));
		
		msv(HIM"$n�۹�һ���������������������$N...\n\n"NOR, me, target);
		target->command("grin");

		tired(target, skill / 2);
		tired(me, 0);
		call_out("love2_done", DURATION * SEC_PER_HB, me, target);

		SKILL_D("pansi-dafa")->random_level_up(me);
	} else {
		msv(HIM"$n�·𲻽���飬��$N�����޶á�\n\n"NOR, me, target);
	}
	return DURATION;
}

void tired(object who, int str)
{
	mapping buff = ([
		"id"		: ID,
		"name"		: NAME,
		"comment"	: "����������",
		"duration"	: DURATION * 3,
		"add_apply" : ([ "strength" : -str ]),
	]);
	int sen = who->query("max_sen") / 3;
	who->receive_curing("sen", sen);	//��������
	who->receive_heal("sen", sen);
	if(who->query_busy() < DURATION) who->start_busy(DURATION);
	BUFF->add(who, buff);
}

void love2_done(object me, object who)
{
	object env = environment(who);
	if(same_env(me, who) && !env->query("no_fight")) {
		msv(CYN"$N����һ��������\n"NOR, who);
		BTL->fight_enemy(who, me);
	}
}

