// cracked by vikee 2/09/2002   vikee@263.net
// spell_d.c.
// mon 12/6/98

#include <ansi.h>

inherit F_DBASE;

#define K					1000
#define XK					2			//相克系数

/* table for 法术相克 
for example,
"dao": ({"yaofa","dengxian-dafa"}),
means, dao can 克制 yaofa and dengxian-dafa.
*/
mapping table = ([
	// xian
	"baguazhou"		: ({"dengxian-dafa"}),
	"buddhism"		: ({"pingtian-dafa"}),
	"dao"			: ({"yaofa","tianmo"}),
	"taiyi"			: ({"moonshentong"}),
	// yao
	"dengxian-dafa"	: ({"moonshentong"}),
	"pingtian-dafa"	: ({"seashentong"}),
	"tianmo"		: ({"buddhism"}),
	"yaofa"			: ({"gouhunshu"}),
	// neutral
	"gouhunshu"		: ({"baguazhou"}),
	"moonshentong"	: ({"tianmo","dao"}),
	"seashentong"	: ({"taiyi"}),
]);

/* determine whether two 法术 are 相克制
if spell1 克制 spell2, then return = 1.
if spell2 克制 spell1, then return = -1.
otherwise, return 0.
*/
int skill_xiangke(string spell1, string spell2)
{
	int neutral=0;
	int result;

	if(undefinedp(table[spell1]) ||
		undefinedp(table[spell2])) return neutral;

	if(member_array(spell1, table[spell2])>-1) {
		// spell2 can 克制 spell1.
		result=-1;
	} else if(member_array(spell2, table[spell1])>-1) {
		// spell1 can 克制 spell2.
		result=1;
	} else {
		result=neutral;
	}

	return result;
}

/* determine whether two players' 法术 are 相克制
only effective between two players,
or a NPC against a player,
can't a player take advantage of a npc.
if obj1 克制 obj2, then return = 1.
if obj2 克制 obj1, then return = -1.
otherwise, return 0.
*/
int check_xiangke(object obj1, object obj2)
{
	int neutral = 0;
	string skill1 = obj1->query_skill_mapped("spells");
	string skill2 = obj2->query_skill_mapped("spells");

	// need at least 20 level of special spells.
	if(obj1->query_skill(skill1,1) < 20) return neutral;
	if(obj2->query_skill(skill2,1) < 20) return neutral;

	return skill_xiangke(skill1, skill2);
}


//法术能量
varargs int spell_power(object ob)
{
	int max_sen = ob->query("max_sen");
	int level = ob->query_skill("spells");
	int exp = ob->query("daoxing");
	
	if(!living(ob)) return 0;
	if(exp < 1) exp = 1;

	level += pow(exp * 3, 0.333);

	if(max_sen > 0) level = level * ob->query("sen") / max_sen;
	else level = 0;

	if(ob->query_temp("no_cast")) level /= 3;

	return level;
}

int attacking_cast_success(object attacker, object target, int success_adj)
{
	int ap = spell_power(attacker);
	int dp = spell_power(target);

	int xk = check_xiangke(attacker, target);
	if(xk == 1) dp = dp / XK;
	if(xk == -1) ap = ap / XK;
	if (!target->is_fighting(attacker)) dp /= 2;		//躲树后搓火球

	trace("ap: " + ap + " dp:" + dp);

	return random(ap) * success_adj / 90 >= dp / 2;
}

private int calc_fali(object who)
{
	int fali = who->query("mana") / 30;

	fali += who->query("eff_sen") / 40;
	fali += who->query("mana_factor") * 4;

	if(!living(who)) fali = 0;
	return fali;
}

int attacking_cast_damage(object attacker, object target, int damage_adj)
{
	int a_fali = calc_fali(attacker);
	int d_fali = calc_fali(target);
	int damage = a_fali / 2 * damage_adj / 100;

	trace("a_fali:" + a_fali + " d_fali:" + d_fali + " damage:" + damage);

	//if(damage > 1000) damage = 1000;
	
	if(a_fali < random(d_fali / 10)) damage = -damage / 2;

	return damage;
}

//weiqi 981206
//this function can be called when want apply a damage to a victim while allow
//the victim use his/her self-made fabao to defense.
void apply_damage(object winner, object victim, 
	int damage, string damage_type, string msg_hit)
{
	int damage_kee = 0;
	int damage_sen = 0;
	int adjust = victim->query_temp("apply/anti_magic");

	if( damage <= 0 ) return;

	if(damage_type == "kee")
		damage_kee = damage;
	else if(damage_type == "sen")
		damage_sen = damage;
	else {
		damage_kee = damage;
		damage_sen = damage;
	}

	damage_kee -= adjust / 2;
	damage_sen -= adjust / 2;


	if(damage_kee > 0 || damage_sen > 0)
		message_vision(msg_hit, winner, victim);
	else
		message_vision("\n只见$N身上法力激荡，将$n的攻势尽数化解。\n", victim, winner);


	if( damage_kee > 0 ) {
		victim->receive_damage("kee", damage_kee, winner);
		victim->receive_wound("kee", damage_kee/2, winner);	
		COMBAT_D->report_status(victim);	
	}
	if( damage_sen > 0 ) {
		victim->receive_damage("sen", damage_sen, winner);
		victim->receive_wound("sen", damage_sen/2, winner);	
		COMBAT_D->report_sen_status(victim);
	}

	return;
}

/*
weiqi 981206
attacking-cast...called from spells function.
a typical call would be:

SPELL_D->attacking_cast(
me, 
//attacker 
target, 
//target
success_adj, 	
//success adjustment
damage_adj, 	
//damage adjustment
"both", 		
//damage type: could be "qi"/"kee", "shen"/"sen", ...default "both"
HIC "$N几个指头迅速捻动，突然张嘴一喷！红橙黄三道火焰呼！地一声向$n卷去！\n" NOR,
//initial message
HIC "结果$n被烧得焦头烂额！\n" NOR, 
//success message
HIC "但是$n轻轻一跳就躲了开来。\n" NOR, 
//fail message
HIC "但是火焰被$n以法力一逼，反向$N回卷而去！\n" NOR, 
//backfire initial message
HIC "结果太乙真火反噬，$n被烧得焦头烂额！\n" NOR
//backfire hit message. note here $N and $n!!!
);
*/
void attacking_cast(
	object attacker, 
	object target, 
	int success_adj, 
	int damage_adj, //default value is 100 for this 2 parameters.
	string damage_type, //must be "shen"/"sen", "qi"/"kee" or "both"(default)
	string msg_init, 
	string msg_success, 
	string msg_fail, 
	string msg_backfire_init,
	string msg_backfire_success)
{
	int damage;

	//first, show the initial message...
	message_vision( msg_init, attacker, target );

	//calculate if the casting can happen...
	if( attacking_cast_success(attacker, target, success_adj) == 0 ) {
		message_vision( msg_fail, attacker, target );
		//let the target kill attacker.
		target->kill_ob(attacker);	
		return;
	}

	damage = attacking_cast_damage(attacker, target, damage_adj);
	if( damage > 0 ) //attacker hit target
		apply_damage(attacker, target, damage, damage_type, msg_success);
	else if( damage < 0 ) {
		message_vision(msg_backfire_init, attacker, target);
		apply_damage(target, attacker, -damage, damage_type, msg_backfire_success);
	}
	else //damge=0
		message_vision(HIB "结果正好被$N以法力逼住，谁也没有吃亏。\n" NOR, target);

	//let the target kill attacker.
	target->kill_ob(attacker);

	return;
}

void create()
{
	seteuid(getuid());
	set("name", "spell精灵");
	set("id", "spelld");

}

