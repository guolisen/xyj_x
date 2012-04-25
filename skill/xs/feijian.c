
#include <ansi.h>
#include <combat.h>
#include <xyj_x.h>

inherit SSERVER;

#define NAME	"����Ͷ��"
#define CD		5
#define MSG0	HIW"$NͻȻ��Хһ��������%s"HIW"���ֶ���������һ�����磬ֱ��$n��ȥ��"NOR
#define MSG1	HIW"%s"HIW"�ڿ��д��˸�ת���ַɻص�$N���С�\n"NOR
#define MSG2	HIW"%s"HIW"�ı䷽�򣬡�ৡ���һ����бб���ڵ��ϡ�\n"NOR

void post_feijian(object me, object victim, object weapon, int damage)
{
	if(damage > 0 || damage == RESULT_DODGE) {
		msv(sprintf(MSG1, weapon->name()), me);
	} else {
		msv(sprintf(MSG2, weapon->name()), me);
		weapon->move(environment(me));
	}
}

mapping _feijian = ([
	"damage"		: 160,
	"dodge"			: -10,
	"parry"			: -10,
	"damage_type"	: "����",
	"action"		:  HIW"$w"HIW"�ڿ��лó��������⣬����Ͷ�ְ㣬��$n��$l��ȥ",
	"post_action"	: (: post_feijian :)
]);

int perform(object me, object target)
{
	object weapon = me->query_temp("weapon");
	int enhance = me->query_skill("throwing", 1) * 2;
	mapping req = ([
		"skill1"	: ([ "ningxie-force" : 50, "bainiao-jian" : 50,  "throwing" : 50 ]),
		"prop"		: ([ "force"	: 100 ]),
	]);

	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("��Ҫ����˭��");
	
	if(!BTL->require(me, NAME, req)) return 1;
	if(!cd_start(me, "im_pfm", CD)) return notify_fail("�����õ�̫��̫�ľͲ����ˡ�\n");

	me->add("force", -100);
	
	msv(sprintf(MSG0, weapon->name()), me, target);
	me->set("actions", _feijian);
	me->add_temp("apply/attack", enhance);				//throwing��������

	COMBAT_D->do_attack(me, target, weapon);
	
	me->add_temp("apply/attack", -enhance);
	me->reset_action();

	BTL->fight_enemy(target, me);
	
	return 1;
}
