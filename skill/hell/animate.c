// animate.c

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>


#define CD			15
#define DURATION	60


object animate(object who, object target);

int cast(object me, object target)
{
	object zombie;
	int skill = me->query_skill("gouhunshu", 1);

	if( me->query("mana") < skill ) return notify_fail("��ķ���������\n");
	if(!cd_start(me, "invoke", CD)) return notify_ok("����ʱ����������ʬ��\n");
	
	me->add("mana", -skill);

	zombie = animate(me, target);
	zombie->add_temp("apply/attack", skill / 4);
	zombie->set_temp("is_zombie", 1);

	zombie->set("chat_chance_combat", 30);
	zombie->set("chat_msg_combat", ({ (: call_other, zombie, "exert_function", "sheqi" :), }));	
	zombie->set("long",	"����һ�߱����÷�����ƵĽ�ʬ�������԰׵����Ͽ������κ�ϲŭ���֡�\n");
	zombie->set("cps", 10000);
	zombie->set("per", 10);

	zombie->set_life(DURATION, "$N�����ص�����ȥ����Ϊһ̲Ѫˮ��\n");
	return 5;
}

object animate(object who, object target)
{
	object zombie = GUARD->new_hufa(who);
	string name;

	if(target) {
		name = target->query("victim_name")  + "�Ľ�ʬ";
		message_vision(CYN"$N�������ϵ�$n�૵����˼������$n�鴤�˼��¾�վ��������\n"NOR, who, target);
		destruct(target);
	} else {
		name = "������ʬ";
		message_vision(CYN"$N�૵����˼�������������һֻ�ɿݵ��֣�����" + name + "���������˳�����\n"NOR, who);
	}
	zombie->set_name(name, ({ "zombie" }));
	return zombie;
}