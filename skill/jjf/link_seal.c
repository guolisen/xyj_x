
#include <skill.h>
#include <ansi.h>

inherit COMBINED_ITEM;

#define MSG0	HIC"\n$N��һ�����š�����һ�ӣ�������һ��$n������\n"NOR
#define MSG1	"$N����һ���������޵ĺ�"


void create()
{
	set_name("���������", ({"link seal", "seal"}));
	set_weight(10);
	if(clonep())
		set_default_object(__FILE__);
	else {
		set("long","һ�Ż����˷�����ҷ�ֽ�������и����ġ��ꡱ�֡�\n");
		//modified by huadao for jjf.2010-9-27
		set("unit", "��");
		set("base_unit", "��");
		set("value", 0);
		set("no_put",1);
		set("no_sell",1);
	}
	set_amount(1);
	setup();
}


int ji_ob(object victim)
{
	object seal = this_object();
	object me = this_player();
	object where = environment(me);

	int damage, ap, dp;

	if(me->is_busy())
		return notify_fail("����æ���أ��޷��������귨����\n");
	//add by huadao 20100629 .
	if (wizardp(victim) && !wizardp(me))
		return notify_fail("�Һ�����ˣ���ۣ��󵨣�\n");
	if( !victim)
		return notify_fail("��������˲������\n");
	if( where->query("no_magic"))
		return notify_fail("���ﲻ�ܼ������귨����\n");
	if( !me->is_fighting())
		return notify_fail("ֻ��ս���в��ܼ������귨����\n");
	if( (int)me->query("mana") < 100 )
		return notify_fail("��ķ������ܿ��������귨����\n");
	if( (int)me->query("sen") < 100 )
		return notify_fail("��ľ����㣬���Ѽ�Ԧ�����귨����\n");

	message_vision(HIC"\n$N��һ�����š�����һ�ӣ�������һ��$n������\n"NOR, me, seal);
	message_vision(HIC"$n��������һ�·ɵ���գ�ֻ��ͻ����ƣ����һ�������$NϮȥ��\n"NOR, victim,seal);

	ap = spell_power(me)  * me->query_kar();
	dp = spell_power(victim) * victim->query_kar();

	if(me->query_skill_mapped("spells") != "baguazhou") ap /= 3;

	if(random(ap) > dp * 8 / 10) {

		damage = me->query("max_mana") / 20 + me->query("eff_sen") / 30;
		damage -= victim->query("max_mana") / 20 + victim->query("eff_sen") / 30;
		damage += me->query("mana_factor") - victim->query("mana_factor") / 2;

		trace("damage:" + damage);

		if(damage > 0){
			message_vision(HIC"\n$N����������������������ţ���ʱ���˸����ˡ�\n"NOR,victim);
			victim->start_busy(damage / 10);
		} else {
			message_vision(HIC"\n$N���˼��������˹�ȥ��\n"NOR,victim);
		}
	} else {
		message_vision(HIC"\n˭֪��$N���˹�ȥ��\n"NOR,victim);
	}

	if( !victim->is_fighting(me) ) {
		if( living(victim) ) {
			if( userp(victim) ) victim->fight_ob(me);
			else
				victim->kill_ob(me);
		}
		me->kill_ob(victim);
	}
	me->add("mana", -50);

	me->start_busy(2 + 1);
	//modified by huadao for jjf.2010-9-27
	add_amount(-1);
	//	destruct(seal);
	return 1;
}

int ji(string target)
{
	object seal = this_object();
	object me = this_player();
	string name = seal->query("name");
	object victim;

	if(!target) return notify_fail("�����˭��"+name+"��\n");

	victim = present(target,environment(me));
	seal->ji_ob(victim);
	return 1;
}

