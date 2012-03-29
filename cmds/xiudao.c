
#include <xyj_x.h>
#include <ansi.h>

inherit F_CLEAN_UP;

#define ID							"xiudao"
#define NAME						"�޵�"
#define DURATION					60			//����ʱ��
#define DX_GAIN						3100		//300 spells��3��/Сʱ��72��/��


int gain(int spells)
{
	return DURATION * DX_GAIN * spells / 300 / 3600;
}

int before_reward(mapping buff)
{
	object me = buff["me"];
	int base_dx = gain(150);
	int dx = gain(me->query_skill("spells"));
	int dx1 = dx - base_dx;						//�����������沿��Ҫ�����;
	int xiudao_room = environment(me)->query("xiudao_room");
	
	if(xiudao_room && TASK->query_norm(me) > dx1)
		TASK_EXC->do_reward(me, "�Լ�", "�޵�", ([ DEXP : dx1 ]));
	else
		dx = min2(dx, base_dx);
	me->add("daoxing", dx);
}

int main(object me, string arg)
{
	return start_xiu(ID,
		NAME,
		DURATION,
		HIY"$N�����۾�����ϥ���£�����ĬĬ���֪��˵Щʲô��\n"NOR,
		HIY"$N���������۾�������һ����վ��������\n"NOR,
		0,
		(["kee" : 20, "sen" : 20]),
		0,
		(["spells" : 1])
		0,
		(: before_reward :)
	);
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

