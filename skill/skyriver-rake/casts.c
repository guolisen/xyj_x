// by firefox 02/09/2010

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

#define ID				"fireback"
#define NAME			HIW"��������"NOR
#define CD				30


mapping* casts = ({
	([
		"name"		: "�Է����",
		"msg"		: HIC
			"$N����ָͷѸ������ͻȻ����һ�磡��Ȼ��������������һ����$n��ȥ��\n"
			"���ǻ��汻$n�Է���һ�ƣ�����$N�ؾ��ȥ��\n"
			"����Է�����ɣ�$N���ս��ˣ�\n",
		"prefix"	: "������",
	]),
	([
		"name"		: "����������",
		"msg"		: HIC
			"$N�������˼������ģ�������ֳ����У���Ҷ�����ߣ�������ִ\nһ���޴��ޱȵĵ����ƣ�������һ����$n��ͷ���£�\n"
			"���ǵ����Ʊ�$n�Է���һ���������ҵ���$N�Ķ��ţ�\n"
			"����Ҹ����ţ�$N���ҵ���ͷ�ǰ���\n",
		"prefix"	: "��ͷ����",
	])
});


int perform(object me, object target)
{
	mapping req = ([
		"cd"		: ([ ID					: 1 ]),
		"skill1"	: ([ "skyriver-rake"	: 250 ]),
		"ex_class"	: ([ "������" : 1 ]),
		"prop"		: ([ "force"			: 10 ]),
	]);
	mapping cast = random1(casts);
	mapping buff = ([
		"id"		: ID,
		"name"		: NAME,
		"comment"	: "�������ұ����ˡ�",
		"class"		: "������",
		"duration"	: CD - 5,
		"temp"		: ([
			"apply/name"	: ({ cast["prefix"] + me->name() }),

		]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("��˭��\n");
	if(!BTL->require(me, NAME, req)) return 1;
	BTL->pay(me, req["prop"]);
	
	BTL->start_cd(me, ID, NAME, CD);

	BUFF->add(me, buff);
	message_vision(cast["msg"] + NOR, me, target);

	me->receive_wound("kee", 500, me);
	me->receive_wound("sen", 500, me);
	COMBAT_D->report_status(me);
	COMBAT_D->report_sen_status(me);

	BTL->fight_enemy(target, me);
	me->start_busy(1);
	return 1;
}
