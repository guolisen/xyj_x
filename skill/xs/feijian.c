
#include <ansi.h>
#include <combat.h>
#include <xyj_x.h>

inherit SSERVER;

#define NAME	"飞鸟投林"
#define CD		5
#define MSG0	HIW"$N突然清啸一声，掌中%s"HIW"脱手而出，化做一道长虹，直向$n飞去！"NOR
#define MSG1	HIW"%s"HIW"在空中打了个转，又飞回到$N手中。\n"NOR
#define MSG2	HIW"%s"HIW"改变方向，“唰”的一声，斜斜插在地上。\n"NOR

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
	"damage_type"	: "刺伤",
	"action"		:  HIW"$w"HIW"在空中幻出道道剑光，飞鸟投林般，向$n的$l扑去",
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
	if(!target) return notify_ok("你要攻击谁？");
	
	if(!BTL->require(me, NAME, req)) return 1;
	if(!cd_start(me, "im_pfm", CD)) return notify_fail("绝招用的太多太滥就不灵了。\n");

	me->add("force", -100);
	
	msv(sprintf(MSG0, weapon->name()), me, target);
	me->set("actions", _feijian);
	me->add_temp("apply/attack", enhance);				//throwing增加命中

	COMBAT_D->do_attack(me, target, weapon);
	
	me->add_temp("apply/attack", -enhance);
	me->reset_action();

	BTL->fight_enemy(target, me);
	
	return 1;
}
