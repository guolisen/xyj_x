// animate.c

inherit F_CLEAN_UP;

#include <ansi.h>

#define CD			15
//�ж��Ƿ���ҹ��
#define at_night() (NATURE_D->query_current_day_phase() / 6)

object animate(object who, object target);

int cast(object me, object target)
{
	object zombie;
	int skill = me->query_skill("gouhunshu", 1);

	if( !me->is_fighting() ) return notify_fail("��ֻ����ս���в���ʹ�ø�������\n");
	if( me->query("mana") < 200 ) return notify_fail("��ķ���������\n");
	if(!cd_start(me, "invoke", CD)) return notify_ok("����ʱ����������ʬ��\n");

	if(target && !target->is_corpse()) target = 0;

	if(!target && !at_night()) return notify_fail("��Ҫ������һ��ʬ�壿\n");

	
	me->add("mana", -50);

	zombie = animate(me, target);
	
	if(target) {
		message_vision(CYN"$N�������ϵ�$n�૵����˼������$n�鴤�˼��¾�վ��������\n"NOR, me, target);
		destruct(target);
	}
	else
		message_vision(CYN"$N�૵����˼�������������һֻ�ɿݵ��֣�����$n���������˳�����\n"NOR, me, zombie);

	zombie->animate(me);
	zombie->reset_action();
	zombie->add_temp("apply/attack", skill / 4);

	call_out("dest_zombie", 60, zombie);
	return 5;	//3+random(5);
}

void dest_zombie(object zombie)
{
	if(zombie) zombie->die();
}

object animate(object who, object target)
{
	object zombie;
	string name = target ? target->query("victim_name") : "����";

	seteuid(getuid());
	zombie = new("/obj/npc/zombie");
	zombie->set_name( name + "�Ľ�ʬ", ({ "zombie" }) );
	zombie->move(environment(who));
	zombie->set_temp("invoker", who);
	return zombie;
}