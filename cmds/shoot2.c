
// shoot.c  by bbs May 27, 1998

#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>
#include "valid_kill.h";

#define THR		100
#define CD		3

//��ʼno_move������ս������ֹ

#define MSGS "$N�ó�%s����%s�ϣ���%s����ȥ��\n";

#define MSG0 HIW"����һ�������죬һ��������$N��ȥ!\n"NOR
#define MSG1 CYN"$NӦ������������ˤ�ڵ��ϡ�\n"NOR
#define MSG2 CYN"$Nһ����������������\n"NOR
#define MSG3 CYN"$Nһ̧�֣�ץסһ֧$n��\n"NOR

int is_safty(object env) { return env->query("no_fight") || env->query("no_magic"); }

//���Ҽ����ȼ���������
object find_arrow(object me, string arrow_id)
{
	object bag, arrow;
	foreach(object ob in all_inventory(me)) {
		if(ob->query("equipped") && ob->query("bag_prop/shoot_cd")) {
			bag = ob;
			break;
		}
	}
	if(bag) arrow = present(arrow_id, bag);
	if(!arrow) arrow = present(arrow_id, me);
	if(arrow->query("arrow_prop")) return arrow;
	return 0;
}

//����Ŀ��
object find_victim(object env, string victim_id)
{
	mapping exits = env->query("exits");
	object victim;
	if(mapp(exits)) {
		foreach(mixed v in values(exits)) {
			object room = objectp(v) ? v : load_object(v);
			if(room == env || is_safty(room)) continue;
			victim = present(victim_id, room);
			if(victim) return victim;
		}
	}
	return 0;
}

int hit_rate(object me, object victim, int accuracy)
{
	mapping cmps = ([
		"prop"		: ([ CEXP : 1, "spi" : 1, "str" : -1, "sen" : 1, "max_sen" : -1 ]),	//������Ŀ���
		"skill"		: ([ "archery" : 3, "dodge" : 2 ]),
		"temp"		: ([ "no_move" : -1 ]),
	]);
	int rate = BTL->cmp_random20(me, victim, cmps) + accuracy;
	if(!living(victim)) return 1000;
	if(me->is_fighting()) rate -= 20;
	if(!cd_end(victim, "be_shot")) rate -= 40;
	if(victim->is_fighting()) rate += 10;
	if(victim->is_busy()) rate += 10;
	trace("rate:" + rate);
	return rate;
}

int main(object me, string arg)
{
	object env = environment(me);
	object bow = me->query_temp("weapon");
	mapping bow_prop= bow ? bow->query("bow_prop") : 0;
	object arrow, victim;
	string arrow_id, victim_id;
	
	if(!bow_prop) return notify_fail("�������Ū�Ź���\n");
	if(me->is_busy()) return notify_fail("��������æ�š�\n");
	if(is_safty(env)) return notify_fail("��ȫ���ڽ�ֹ�����\n");
	if(!arg || sscanf(arg, "%s on %s", arrow_id, victim_id) != 2)
		return notify_fail("ָ���ʽ��shoot <ĳ��> on <ĳ��>\n");

	arrow = find_arrow(me, arrow_id);
	if(!arrow) return notify_fail("��Ҫ��ʲô����\n");
	victim = find_victim(env, tar_id);
	if(!victim) return notify_fail("��Ҫ��˭��\n");;

	msv(MSG0, victim);
	rate = hit_rate(me, victim, bow_prop["accuracy"]);
	if(rate > THR) {
		mapping arrow_prop = arrow->query("arrow_prop");
		int armor = victim->query_temp("apply/armor") - arrow_prop["anti_armor"];
		int power = min2(bow_prop["power"]

		wound=random(damage-(int));
		victim->receive_damage("kee", damage, me);
		if(wound >0) victim->receive_wound("kee", wound, me);

		msv(MSG1, victim);
		if(!victim->is_busy) victim->start_busy(1);
		if(ratio < THR + 20) me->improve_skill("archery", 1 + random(me->query("int")));
	} 
	else if(rate > THR / 2) {
		msv(MSG2, victim);
	} else {
		object ob = new(base_name(arrow));
		ob->set_amount(1);
		msv((ob->move(victim) ? MSG3 : MSG2), victim);
	}
	me->kill_ob(victim);
	arrow->add_amount(-1);
	cd_start(victim, "be_shot", CD * 10);		//�м��󾯾�
	me->start_busy(CD);
	return 1;
}



int help(object me)
{
   write( @HELP
ָ���ʽ: shoot <something> on <someone>

��һָ�����������ĳ�������
HELP
   );
   return 1;
}


/*

	if(targ == me->query("id"))
		return notify_fail("����ɱӦ����suicide�ɣ�\n");
	if( !objectp(ob = present(item, me)))
		return notify_fail("������û�� "+item+"\n");

	if(ob->query("skill_type")!="sword" || ob->query("apply/skill_type")!="archery")
		return notify_fail(ob->query("name")+"���Ǽ���\n");


	success=0;
	if(ob2=me->query_temp("weapon")) {
		if(ob2->query("skill_type")=="blade" && ob2->query("apply/skill_type")=="archery") 
			success=1;
		else {
			if(ob2=me->query_temp("secondary_weapon")) {
				if(ob2->query("skill_type")=="blade" && ob2->query("apply/skill_type")=="archery") 
					success=1;
			}
		}
	}
	if(!success)
		return notify_fail("�������Ū�Ź���\n");

	if( !objectp(victim = present(targ, environment(me))) )
		return notify_fail("��������˭��\n");

	if( !living(victim)) 
		return notify_fail("ʲô�㶼��ɱ��\n");

	if(!valid_kill(me,victim,0)) return 0;

	success=0;
	found=0;
	lucky=0;
	damage=0;
	wound=0;
	ap=COMBAT_D->skill_power(me, "archery", SKILL_USAGE_ATTACK);
	dp=COMBAT_D->skill_power(victim, "dodge", SKILL_USAGE_DEFENSE);
	dp/=2;			// �����ѷ� 
	if(random(ap+dp) > dp) {
		success=1;
		if(ap<dp) lucky=1;
	}
	msg="$N���ִӻ����ͳ�һ"+ob->query("base_unit")+ob->query("name")+"������"+ob2->query("name")+"�ϡ�\n";
	msg+="һ���֣�ֻ��һ���������$n�����ţ�";

	if(success) {
		msg+="$n���ȴû�㿪��\n";
		damage=ob->query("weapon_prop/damage");
		damage+=random(damage);
		damage_bonus=me->query_str();
		foo=ob->hit_ob(me, victim, damage);
		if(stringp(foo)) msg+=foo;
		else if(intp(foo)) damage_bonus+=foo;
		wound=random(damage-(int)victim->query_temp("apply/armor"));
		damage+=(damage_bonus+random(damage_bonus))/2;
		ap=me->query("force");
		dp=victim->query("force");
		while(random(dp)>ap) {
			damage-=damage/3;
			dp/=2;
		}
		if (wizardp(me) && me->query("env/combat")=="verbose")
			tell_object(me, sprintf(GRN "damage: %d, wound: %d\n" NOR, damage, wound));
		if(damage>0) {
			victim->receive_damage("kee", damage, me);
			if(wound >0) victim->receive_wound("kee", wound, me);
			msg+=COMBAT_D->damage_msg(damage,"�˺�");
		}
		if(random(me->query("sen")*100/me->query("max_sen") + me->query_int()*me->query_cps()) > 150) {
			if(lucky) {
				me->improve_skill("archery", 1);
				me->set("combat_exp",me->query("combat_exp")+1);
				if(me->query("potential")-me->query("learned_points")<100)
					me->set("potential",me->query("potential")+1);
			}
		}
	}
	else 
		msg+="���Ǳ�$n�㿪�ˡ�\n";

	if((int)ob->query_amount()==1) {
		if(stringp(ob->query("equipped"))) ob->unequip();
		tell_object(me, "���" + ob->query("name") + "�����ˣ�\n");
	}
	ob->add_amount(-1);

	message_vision(msg, me, victim);
	if(damage > 0) COMBAT_D->report_status(victim);

	if(living(victim)) {
		msg="$nŭ��$N�������ȵ���С�����Ӹҷ������\n";
		message_vision(msg, me, victim);
		if(userp(victim)) victim->fight_ob(me);
		else victim->kill_ob(me);
		me->kill_ob(victim);
	}
	*/