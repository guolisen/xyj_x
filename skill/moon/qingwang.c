
#include <ansi.h>

inherit SSERVER;

#define DURATION			20

void remove_effect(object target,object me);

int cast(object me, object target)
{
	string msg;
	int howlong = DURATION;
	int success, ap, dp, npc_chance;
	object weapon = me->query_temp("weapon");
	object qingwang;

	if( !target ) target = offensive_target(me);
	//        if (!wizardp(me)) return notify_fail("�㲻����ʦ��������������\n");

	if (!weapon || weapon->query("skill_type")!="whip")
		return notify_fail("û�б��ӣ�����ʲô֯��������\n");
	if (me->query_skill_mapped("whip")!="jueqingbian")
		return notify_fail("��û���þ���ޣ�ʹ����������\n");

	if(me->query_skill("spells") < 150 || 
		me->query_skill("moonshentong",1) < 100 ||
		me->query_skill("jueqingbian",1)<100 ||
		me->query_skill("whip")<150)
		return notify_fail("�㻹����������������\n");

	if( !target
		||      !target->is_character()
		||      target->is_corpse()
		||      target==me)
		return notify_fail("�����˭ʹ��������\n");  

	if(me->query_temp("qingwang"))
		return notify_fail("���Ѿ�����һ�����ˣ�\n");  

	if(me->query("mana") < 200 )
		return notify_fail("��ķ���������\n");

	if(me->query("sen") < 10 )
		return notify_fail("���޷����о�����\n");

	me->add("mana", -200);
	me->receive_damage("sen", 10);

	message_vision(HIB"$N�߶�������������"+weapon->name()+"���һ�ţ�����һ�Ŵ�������$n��ͷ������\n"NOR,me,target);

	success = 1;
	ap = me->query_skill("spells") / 10;
	ap = ap * ap * ap /12 ;
	ap += me->query("daoxing") / 1000;
	dp = target->query("daoxing") / 1000;

	ap += me->query_skill("jueqingbian", 1) * 2000 / 1000;
	dp += target->query_skill("dodge", 1) * 2000 / 1000;
	
	ap += me->query("mana") * 200 / 1000;
	dp += target->query("mana") * 200 / 1000;

	if( random(ap+dp)<dp) success = 0;

	if(success == 1 ){
		message_vision(HIB"$N������һƬ���ң���ʹ����ͻȻ���������������˶�������������ͷ��ס��\n"NOR,target);

		seteuid(getuid());
		qingwang=new("/d/obj/fabao/qingwang");
		qingwang->set("target",target);
		qingwang->set("owner",me);
		qingwang->set("weapon",weapon);
		me->set_temp("qingwang",qingwang);
		qingwang->set("time_expired",time() + howlong);

		if (!qingwang->move(environment(target))) {
			message_vision(HIY"$N���Ϸ���һ�������⣬���������ķ��顣\n"NOR,target);
			destruct(qingwang);
		}
		if ((!userp(target)) && npc_chance=target->query("chat_chance_combat")) {
			target->set_temp("chat_chance_combat", npc_chance);
			target->delete("chat_chance_combat");
			call_out("remove_effect", howlong, target, me);
		}
	} else {
		message_vision(HIG"$N�������ѣ���Ϊ����������������һԾ�������������Ϯ����\n"NOR,target);
		me->start_busy(1);
		if( living(target) ) target->kill_ob(me);
	} 

	return 3 + 2;
}
void remove_effect(object target,object me) {
	if (me->query_temp("qingwang")) destruct(me->query_temp("qingwang"));
	if (!target) return;
	target->set("chat_chance_combat",target->query_temp("chat_chance_combat"));
}
