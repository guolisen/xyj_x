// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <ansi.h>
#include <xyj_x.h>

#define ID				"pansi"
#define NAME			HIB"������˿"NOR
#define DURATION		8
#define CD				20

#define MSG0			HIW"$N����ͻȻ�ɳ�һ��������$n��ͷ��ȥ��\n"NOR
#define MSG1			HIW"$n⧲�����������ճ��ԭ�ض������á�\n"NOR
#define MSG2			"$n�������ɣ�һ����ա�\n"NOR
#define MSG3			"$n�ſ�Ѫ���ڣ�����һ�����£�\n"NOR

/*
������˿
��ئ�������˿��
ţħ�������С����(һ������)
*/

void po_lost(object target, int n);

int cast(object me, object target)
{
	int thr = 100;
	mapping req = ([
		"cd"		: ([ ID				: 1 ]),
		"skill1"	: ([ "pansi-dafa"	: 30 ]),
		"prop"		: ([ "mana"			: 50 ]),
	]);
	mapping cmp_parm = ([	//�Է������Ṧ������Ҳ���÷����ֿ�
		"prop"		: ([ "str" : -2, CEXP : 1, DEXP : 1, "sen" : 1, "max_sen" : -1 ]),
		"skill"		: ([ "dodge" : 2, "spells" : 2 ]),
		"temp"		: ([ "no_cast" : -1, "no_move" : -1, "chaofeng_busy" : -1, "fc_pfm_busy" : -1 ]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("��Ҫ��˭��");
	
	if(!BTL->require(me, NAME, req)) return 1;

	BTL->pay(me, req["prop"]);
	BUFF->start_cd(me, ID, NAME, CD);

	msv(MSG0, me, target);

	if(target->is_busy()) thr -= 20;

	if(BTL->cmp_random20(me, target, cmp_parm) > thr) {
		mixed n = target->query_busy();
		n = intp(n) ? max2(n, DURATION) : DURATION;		//���Ը���Ŀ���æ״̬
		target->start_busy(n);
		msv(MSG1, me, target);

		SKILL_D("pansi-dafa")->random_level_up(me);
	} else {
		string msg = (target->query_per() > 18) ? MSG2 : MSG3;
		msv(msg, me, target);
		if(!userp(target) && !random(10)) 
			target->command("say ���С����");
	}
	BTL->fight_enemy(target, me);
	me->start_busy(1);
	return 1;
}
