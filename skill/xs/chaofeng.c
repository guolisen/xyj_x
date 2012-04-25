// firefox 2012.4

#include <ansi.h>
#include <xyj_x.h>

inherit SSERVER;

#define CD		5
#define NAME	"百鸟朝凤"

#define MSG0	HIW"只见$N手中%s"HIW"急颤，幻出满天剑芒，无数%s"HIW"有如百鸟投林般向$n扑来！\n"NOR
#define MSG1	HIW"$n连忙身行一转，连退数步，闪过了这满天花雨般的一击。\n"NOR
#define MSG1	HIW"$n对着$N高声骂道：好啊，敢放暗器，看我怎么收拾你！\n"NOR

int ob_exp(object who)
{
	int exp = who->query("combat_exp");
	exp = pow(max2(10, exp), 0.333);
	return exp;
}

int hit(object me, object target)
{
	 
}

int perform(object me, object target)
{
	object weapon = me->query_temp("weapon");
	int n = weapon->query("anqi/now");
	string type = "剑气";

	mapping req = ([
		"cd"		: ([ ID			: 1 ]),
		"skill1"	: ([ "sword"	: 20,		"bainiao-jian" : 20 ]),
		"skill_map"	: ([ "force"	: "ningxie-force" ]),
		"prop"		: ([ "force"	: 50 ]),
	]);
	mapping cmp_parm = ([
		"prop"		: ([ DEXP : 1 ]),
		"skill"		: ([ "spells" : 2 ]),
		"skill_pair1": ([ ({"whip", "dodge"}) : 3 ]),
	]);
	
	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("你要攻击谁？");

	if(!cd_start(me, "chaofeng", CD)) return notify_fail("绝招用的太多太滥就不灵了。\n");

	if(n < 1) {
		type = "剑气";
		damage = me->query("force_factor")+10; 
	}
	else if (req < 150)
	{ anqi_type=weapon->query("anqi/type"); damage=me->query_temp("apply/damage");}
	else 
	{ anqi_type=weapon->query("anqi/type")+"加着剑气";
	damage=me->query_temp("apply/damage")+me->query("force_factor")+10;}



	if (num_anqi > 10 || num_anqi == 0) max_hit=10;
	else max_hit=weapon->query("anqi/now");

	num_hit=random(max_hit/2)+(max_hit/2);

	if (!target->is_fighting(me)) opfa=30;
	else opfa=15;

	if (target->query("combat_exp")  !=0 ) 
	{
		if (opfa==30 && me->query("combat_exp")>70000000)
			op= 2100000000/target->query("combat_exp");
		else
			op= me->query("combat_exp")*opfa/target->query("combat_exp");
	}
	else op=10;


	hitt=0;	
	for (ii=1;ii<=num_hit;ii++)  
	{if (op > random(100)) hitt++;}


	if (weapon->query("anqi/type")=="孔雀翎") b_unit="支";
	else b_unit="根";
	if (weapon->query("anqi/now") != 0) remain=weapon->query("anqi/now")-num_hit;
	else remain=0;
	weapon->set("anqi/now",remain);
	if (weapon->query("anqi/now") == 0) 

	if (hitt==0)
	{
		
		message_vision(msg, me, target);
		me->start_busy(1);
		/*
		if(!target->is_busy())
		target->start_busy(random(3));
		*/
	}
	else 
	{
		damage=damage*hitt;
		target->receive_damage("kee",damage,me);
		if (random(damage)>target->query_temp("apply/armor"))  {
			target->receive_wound("kee",damage-target->query_temp("apply/armor"),me);
			wound=1;
		}
		msg += HIW "$n躲闪不及，身上"+chinese_number(hitt)+HIW "处中了"+anqi_type+"！\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(1);
		COMBAT_D->report_status(target,wound);
		if(!target->is_busy()) target->start_busy(2);
	}
	
	message_vision(msg, me, target);
	target->kill_ob(me);
	me->set_temp("chaofeng_busy",1);
	call_out("remove_effect",3+2,me);
	return 1;
}

void remove_effect(object me) {
	if (!me) return;
	me->delete_temp("chaofeng_busy");
}
