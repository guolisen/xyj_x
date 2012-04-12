//Last modified by pkyou@2010-3-11

#include <ansi.h>
#include <combat.h>

inherit SSERVER;

#define min2(a, b) ((a) < (b) ? (a) : (b))

int perform(object me, object target)
{
	int spear = me->query_skill("bawang-qiang", 1);
	int mace = me->query_skill("wusi-mace", 1);
	int anti_defense = spear * 2;
	int anti_armor;

	object weapon1 = me->query_temp("weapon");
	object weapon2 = present("mace", me);

	if(!target) target = offensive_target(me);
	if(!target || !me->is_fighting(target) || !living(target))
		return notify_fail("「枪里加锏」只能在战斗中使用！\n");

	if((int)me->query("max_force") < 500)
		return notify_fail("你的内力不够！\n");

	if((int)me->query("force") < 500 )
		return notify_fail("你的内力不足！\n");

	if(spear < 100)	return notify_fail("你的霸王枪级别还不够，使用这一招会有困难!\n");

	if(mace < 100) return notify_fail("你的无私锏级别还不够，使用这一招会有困难!\n");

	if(me->query_skill_mapped("mace") != "wusi-mace")
		return notify_fail("「枪里加锏」必须配合无私锏法!\n");

	if(!objectp(weapon2) || weapon2->query("skill_type") != "mace")		//修复出空手的bug
		return notify_fail("没锏怎么枪里加锏?\n");

	me->add("force", -200);

	message_vision(HIC"\n$N运足精神，抖手刺出一枪!\n"NOR, me, target);

	COMBAT_D->do_attack(me, target, weapon1, TYPE_QUICK);

	message_vision(HIC"\n趁着$n正忙于招架，$N抽出" + weapon2->query("name") + "击出两下。\n"NOR, me, target);

	weapon1->unequip();
	weapon2->wield();
	
	anti_armor = min2(target->add_temp("apply/armor"), mace / 2);

	target->add_temp("apply/armor", -anti_armor);		//隋唐流行钝兵器，就是为了对付重甲
	
	COMBAT_D->do_attack(me, target, weapon2, TYPE_QUICK);
	
	target->add_temp("apply/defense", -anti_defense);	//枪法扰乱，提升锏法命中	
	
	COMBAT_D->do_attack(me, target, weapon2, TYPE_QUICK);

	target->add_temp("apply/defense", anti_defense);
	target->add_temp("apply/armor", anti_armor);

	if( !target->is_fighting(me) ) {
		if( living(target) ) {
			if( userp(target) ) target->fight_ob(me);
			else target->kill_ob(me);
		}
	}

	weapon2->unequip();
	weapon1->wield();

	me->start_busy(2);

	return 1;
}

