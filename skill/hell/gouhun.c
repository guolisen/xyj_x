// gouhun.c
#include <ansi.h>

inherit SSERVER;


//判断是否在夜间
#define at_night() (NATURE_D->query_current_day_phase() / 6)


int cast(object me, object target)
{
	int k = at_night() ? 1 : -1;
	int success_adj = 120 + k * 60;
	int damage_adj = 120 + k * 60;
	int cost = 25 + 2 * me->query("mana_factor");
	int anti_magic = me->query_skill("gouhunshu") * 2 / (1 + me->query("betray/count"));

	if( !target ) target = offensive_target(me);

	if( !target
		|| !target->is_character()
		|| target->is_corpse()
		|| target == me)
		return notify_fail("你要勾自己的魂？\n");

	if((int)me->query("mana") < cost ) return notify_fail("你的法力不够了！\n");

	me->add("mana", -cost);

	target->add_temp("apply/anti_magic", -anti_magic);

	SPELL_D->attacking_cast(
		me, 
		//attacker 
		target, 
		//target
		success_adj, 	
		//success adjustment
		damage_adj, 	
		//damage adjustment
		"sen", 		
		//damage type: could be "qi"/"kee", "shen"/"sen", ...default "both"
		HIC "$N对$n阴阴地笑着：阎王叫你三更死，不敢留你到五更。。。\n" NOR,
		//initial message
		HIC "$n受到$N影响，显然有点魂不守舍了！\n" NOR, 
		//success message
		HIC "但是$n神情专注，对$N理都不理。\n" NOR, 
		//fail message
		HIC "但是$n眼一瞪：光天化日之下，岂由恶鬼横行！\n" NOR, 
		//backfire initial message
		HIC "结果$n反而有点魂不守舍了！\n" NOR
		//backfire hit message. note here $N and $n!!!
	);

	target->add_temp("apply/anti_magic", anti_magic);

	//me->start_busy(1 + random(2));
	return 5;	//3+random(5);
}
