// cracked by vikee 2/09/2002   vikee@263.net
// exercise.c

#include <skill.h>

inherit F_CLEAN_UP;

int finishb(object me);
int main(object me, string arg)
{
	int sen_cost, busy_time;
	object where = environment(me);

	seteuid(getuid());

	if(environment(me)->query("no_fight")  ||
		environment(me)->query("no_magic") )
		return notify_fail("���ﲻ�����������ĵط���\n");

	me->set_temp("pending/full", (arg == "full"));

	if(arg == "full")
		sen_cost = me->query("sen") - 20;
	else if(arg == "max")
		sen_cost = me->query("sen") - 20;
	else if(!arg || !sscanf(arg, "%d", sen_cost))
		return notify_fail("��Ҫ�����پ���ڤ˼��\n");

	if( sen_cost <= 0 && me->query_temp("pending/meditating") ){
		//                remove_call_out("exec_int");
		call_out("finish", 1, me);
		return 1;
	}

	if (me->is_busy() || me->query_temp("pending/meditating"))
		return notify_fail("��������æ���ء�\n");

	if( me->is_fighting() )
		return notify_fail("ս���в���ڤ˼��\n");

	if( !stringp(me->query_skill_mapped("spells")) )
		return notify_fail("��������� enable ѡ����Ҫ�õķ�����\n");

	if( sen_cost < 20 ) return notify_fail("������Ҫ�� 20 �㡸���񡹲���ڤ˼��\n");

	if( (int)me->query("sen") < sen_cost )
		return notify_fail("���������ǲ���,����������Ƿ��ˡ�\n");

	write("����ϥ����������ڤ˼��һ�����\n");

	busy_time=sen_cost/20;
	me->start_busy(busy_time*2 + 1);
	me->set_temp("pending/meditating", 1);
	call_out("exec_int", 1, me, where, busy_time);	
	//	call_out("finish",busy_time+1, me, sen_cost);
	return 1;
}
int exec_int(object me, object where, int busy_time)
{
	object wherenow;
	int mana_gain;
	wherenow = environment(me);

	if(!me) return 1;
	if(!me->query_temp("pending/meditating")) return 1;

	if( wherenow!=where ){
		//		remove_call_out("exec_int");
		finishb(me);
		return 1;
	}

	if(!living(me)) return finishb(me);

	mana_gain = (int)me->query_skill("spells",1)/10
		+(int)me->query_spi()/3 + random(3);

	mana_gain *= 2;

	if (mana_gain < 5) mana_gain = 5;
	if (mana_gain > 40 * 2) mana_gain = 40 * 2;

	mana_gain *= 2;

	me->receive_damage("sen", 20);
	me->add("mana", mana_gain);

	if(me->query("mana") > me->query("max_mana") * 2) {

		if(me->query_temp("pending/full")) {
			me->set("mana", me->query("max_mana") * 2);
		}
		else if( me->query("max_mana") >= me->query_max_mana() ) {
			tell_object(me,	"����ķ������ӵ�˲�����Ȼ��������һƬ���ң��ƺ������������Ѿ�����ƿ����\n");
			me->set("mana", me->query("max_mana") * 2);
		}else{
			tell_object(me, "��ķ�����ǿ�ˣ�\n");
			me->add("max_mana", 1);

			if( me->query("max_mana") > me->query("maximum_mana"))
				me->set("maximum_mana", me->query("max_mana"));
			me->set("mana", me->query("max_mana"));
		}
		
		//                remove_call_out("exec_int");
		call_out("finish", 1, me);
		return 1;
	}
	if (busy_time>1){
		busy_time--;
		call_out("exec_int", 1, me, where, busy_time);
	} else {
		call_out("finish", 1, me);
	}
	return 1;
}
int finishb(object me)
{
	me->delete_temp("pending/meditating");
	me->start_busy(1);
	return 1;
}
int finish(object me)
{
	me->delete_temp("pending/meditating");
	me->start_busy(1);
	tell_object(me, "���й���ϣ���ڤ˼�лع�������\n");
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : meditate|mingsi [<�ķѡ��񡹵�����Ԥ��ֵ 30>]
meditate|mingsi 0 ��ֹͣڤ˼

����ڤ˼��������ľ�������Ч�ؼ������۳��ܹ�����ʩչ����������
�����������Լ��ķ�����

HELP
);
	return 1;
}