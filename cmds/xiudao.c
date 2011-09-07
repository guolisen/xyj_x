
#include <xyj_x.h>
#include <ansi.h>

inherit F_CLEAN_UP;

#define PROP						"sitting"
#define DURATION					60			//����ʱ��
#define DX_GAIN						3100		//300 spells��3��/Сʱ��72��/��

int main(object me, string arg)
{
	object env = environment(me);

	seteuid(getuid());

	if(env->query("no_fight") || env->query("no_magic"))
		return notify_fail("��ȫ���ڽ�ֹ������\n");

	if(me->is_busy() || me->query_temp(PROP) || me->is_fighting())
		return notify_fail("��������æ���ء�\n");

	if(me->query("sen") < 100 || me->query("kee") < 100)
		return notify_fail("��״̬���ѣ���������Ҫ�߻���ħ��\n");

	message_vision(HIY"$N�����۾�����ϥ���£�����ĬĬ���֪��˵Щʲô��\n"NOR, me);

	me->start_busy(DURATION / 2 + 1);
	me->set_temp(PROP, 1);
	call_out("finish", DURATION, me, env->query("xiudao_room"));
	return 1;
}

int gain(int spells)
{
	return DURATION * DX_GAIN * spells / 300 / 3600;
}


void finish(object me, int xiudao_room)
{
	int base_dx = gain(150);
	int dx, dx1;

	if(!me) return;

	dx = gain(me->query_skill("spells"));
	dx1 = dx - base_dx;						//�����������沿��Ҫ�����

	if(xiudao_room && TASK->query_norm(me) > dx1)
		TASK_EXC->do_reward(me, "�Լ�", "�޵�", ([ DEXP : dx1 ]));
	else
		dx = min2(dx, base_dx);

	me->delete_temp(PROP);

	message_vision(HIY "$N���������۾�������һ����վ��������\n" NOR, me);

	me->add("daoxing", dx);
	tell_object(me, HIC "��ĵ���������" + chinese_number(dx * 3) + "ʱ����\n" NOR);

	me->receive_damage("sen", 20);
	me->receive_damage("kee", 20);
	me->improve_skill("spells", 1 + random(dx) / 10);
}

int help(object me)
{
        write(@HELP
ָ���ʽ : xiudao

������������ߵ��С�
HELP
        );
        return 1;
}


int test()
{
	main(this_player(), 0);
}

