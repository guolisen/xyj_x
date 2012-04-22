
#include <xyj_x.h>
#include <ansi.h>
#include "/cmds/std/valid_kill.h"

inherit F_CLEAN_UP;

#define CD		1
#define THR		100

int main(object me, string arg)
{
	object env = environment(me);
	string what, who;
	object ob, victim;
	
	if(env->query("no_fight")) return notify_fail("�����ֹ���ԡ�\n");
	if(!arg || sscanf(arg, "%s from %s", what, who) != 2)
		return notify_fail("ָ���ʽ��steal <��Ʒ> from <����>\n");
	
	victim = present(who, env);

	if(!victim || victim == me) return notify_fail("�������ԵĶ��������\n");
	if(!valid_kill(me, victim, 0)) return 0;
	if(!wizardp(me) && wizardp(victim)) return notify_fail("��Ҳ���͵��ʦ���ϵĶ�����\n");

	if(!ob = present(what, victim)) {
		object* inv = all_inventory(victim);
		if(!sizeof(inv)) return notify_fail( "�Է����Ͽ�����û��ʲô������͵��\n");
		ob = inv[random(sizeof(inv))];
	}
	if(!cd_start(me, "steal", CD)) return notify_fail("��������Σ����̫���ˡ�\n");

	write("�㲻����ɫ����������" + victim->name() + "���ȴ��������� ...\n\n");
	call_out("complete_steal", 3, me, victim, ob);
	return 1;
}

private void complete_steal(object me, object victim, object ob)
{
	if(!me || !living(me)) return;
	else if(!me->close_to(victim)) tell_object(me, "̫��ϧ�ˣ������ֵ�Ŀ���Ѿ����ˡ�\n");
	else if(!ob || ob->query("no_give") || ob->query("no_get")) tell_object(me, "���������˸��ա�\n");
	else if(me->is_busy()) tell_object(me, "���Թ˲�Ͼû�������֡�\n");	
	else {		
		int ratio = 1000;
		if(living(victim)) {
			mapping cmps = ([
				"prop"		: ([ CEXP : 1, "spi" : 2, "per" : 1, "str" : -1, "sen" : 1, "max_sen" : -1 ]),
				"skill"		: ([ "stealing" : 3, "dodge" : 2 ]),
				"temp"		: ([ "no_move" : -1 ]),
			]);
			ratio = BTL->cmp_random20(me, victim, cmps);
			if(me->is_fighting()) { me->start_busy(3); ratio -= 10; }
			if(!cd_end(me, "thief")) ratio -= 10;
			if(!cd_end(victim, "stolen")) ratio -= 40;
			if(victim->is_fighting()) ratio -= 10;
			if(victim->is_busy()) ratio += 10;
			if(ob->query("equipped")) ratio -= 80;
		}
		trace("steal:" + ratio);
		if(ratio > THR) {
			if(!ob->move(me)) {
				tell_object(me, "������" + ob->unit_name() + "����̫���ˣ����ò�������\n");
				return;
			}
			if(random(ratio) * 4 < THR)
				message_vision(CYN"$N��С�ĺ�$nײ�˸��������Ҵ��ܿ���\n"NOR, me, victim);

			tell_object(me, HIW "�����ˣ�\n\n" NOR);
			tell_object(me, "��͵��" + ob->unit_name() + "��\n");
			if(ratio < THR + 20) me->improve_skill("stealing", 1 + random(me->query("int")));
		} 
		else if(random(ratio) * 2 > THR) {
			tell_object(me, victim->name() + "�������һתͷ���㼱æ�������˻�ȥ��\n���ã�û�б����֡�\n");
		} else {
			tell_object(me, HIR"��⣡��ʧ���ˣ�\n\n"NOR);
			message_vision("$Nһ��ͷ�����÷���$n������ץ��$P���ϵ�" + ob->name() + "��\n\n"
				+ "$N�ȵ�������ʲô����\n\n", victim, me);
			if(userp(victim)) victim->fight_ob(me);
			else victim->kill_ob(me);
			me->fight_ob(victim);
			me->start_busy(5);
			me->add("thief", 1);
			cd_start(me, "thief", CD * 5);				//���к󱻴��ڷ���
			cd_start(victim, "stolen", CD * 10);		//�����󾯾�
		}
	}
}

int help(object me)
{
write(@HELP
ָ���ʽ : steal <ĳ��> from <ĳ��>

���ָ�������л���͵���������ϵĶ������ɹ���, ��Ȼ����ܻ��
������Ʒ������, ����ʧ��, ������ʧ���ʱ��, ����ʧ��ʱ��Ȼ��
�ø�������, ������ʲô����......�����Լ�ȥ�����ޡ�
HELP
    );
    return 1;
}
