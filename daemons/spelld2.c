// spell_d.c.
// mon 12/6/98

#include <ansi.h>

inherit F_DBASE;

#define K					1000
#define XK					2			//���ϵ��


mapping family_spells_ = ([
	"�Ϻ�����ɽ"		: "buddhism",
	"����ɽ���Ƕ�"	: "dao",
	"��ׯ��"			: "taiyi",
	"�¹�"			: "moonshentong",

	"������"			: "baguazhou",
	"���޵ظ�"		: "gouhunshu",
	"��������"		: "seashentong",

	"��ѩɽ"			: "dengxian-dafa",
	"�ݿ�ɽ�޵׶�"	: "yaofa",
	"���ƶ�"			: "pingtian-dafa",
	"��˿��"			: "pansi-dafa",
]);

// �����ɱ��ŷ���������firefox 2011.11
int family_bonus(object who)
{
	string skill = who->query_skill_mapped("spells");
	string family = who->query("family/family_name");

	return !who->query("betray/count") && (family_spells_[family] == skill);
}


// table for ������� 
mapping xiangke = ([
	// xian
	"baguazhou"		: ({"dengxian-dafa"}),
	"buddhism"		: ({"pingtian-dafa"}),
	"dao"			: ({"yaofa"}),
	"taiyi"			: ({"moonshentong"}),
	// yao
	"dengxian-dafa"	: ({"moonshentong"}),
	"pingtian-dafa"	: ({"seashentong"}),
	"yaofa"			: ({"gouhunshu"}),
	// neutral
	"gouhunshu"		: ({"baguazhou"}),
	"moonshentong"	: ({"dao"}),
	"seashentong"	: ({"taiyi"}),
]);

//��������
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

	if (!target->is_fighting(attacker)) dp /= 2;		//����������

	trace("ap: " + ap + " dp:" + dp);

	return random(ap) * success_adj / 100 >= dp / 2;			//firefox 2011.11
}

private int calc_fali(object who)
{
	int fali = who->query("mana_factor") * 5;
	fali += who->query("eff_sen") / 40;

	if(!living(who)) fali = 0;
	return fali;
}

int attacking_cast_damage(object attacker, object target, int damage_adj)
{
	int a_fali = calc_fali(attacker);
	int d_fali = calc_fali(target);
	int damage = a_fali / 2 * damage_adj / 100;

	trace("a_fali:" + a_fali + " d_fali:" + d_fali + " damage:" + damage);

	if(a_fali < random(d_fali / 5)) damage = -damage / 2;

	return damage;
}

//weiqi 981206
//this function can be called when want apply a damage to a victim while allow
//the victim use his/her self-made fabao to defense.
void apply_damage(object winner, object victim, int damage, string damage_type, string msg_hit)
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
		message_vision("\nֻ��$N���Ϸ�����������$n�Ĺ��ƾ������⡣\n", victim, winner);


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

///attacking cast
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
	
	damage -= damage / 5;									//firefox 2011.11
	if(!family_bonus(attacker)) damage -= damage / 3;

	if( damage > 0 ) //attacker hit target
		apply_damage(attacker, target, damage, damage_type, msg_success);
	else if( damage < 0 ) {
		message_vision(msg_backfire_init, attacker, target);
		apply_damage(target, attacker, -damage, damage_type, msg_backfire_success);
	}
	else //damge=0
		message_vision(HIB "������ñ�$N�Է�����ס��˭Ҳû�гԿ���\n" NOR, target);

	//let the target kill attacker.
	target->kill_ob(attacker);

	return;
}

//���ѡ�����
object random_enemy(object me)
{
	object* arr;

	me->clean_up_enemy();
	arr = me->query_enemy();
	return sizeof(arr) ? random1(arr) : 0;
}

/// do cast
int do_cast(
	object me,
	object target,
	int success_adj,
	int damage_adj,
	string damage_type,
	string msg_init,
	string msg_success,
	string msg_fail,
	string msg_backfire_init,
	string msg_backfire_success,
	int cost,
	int busy,
	int no_cast)
{
	cost += 2 * me->query("mana_factor");

	if(!target) target = random_enemy(me);

	if(!target || !target->is_character() || target->is_corpse() || target == me)
		return notify_fail("��Ҫ��˭ʩ����\n");

	if(me->query("mana") < cost)
		return notify_fail("��ķ������㣡\n");

	me->add("mana", -cost);

	attacking_cast(
		me, 
		target, 
		success_adj,    
		damage_adj,     
		damage_type,          
		msg_init,
		msg_success, 
		msg_fail, 
		msg_backfire_init, 
		msg_backfire_success
	);

	if(busy) me->start_busy(busy);
	return no_cast;
}


void create()
{
	seteuid(getuid());
	set("name", "spell����");
	set("id", "spelld");

}

