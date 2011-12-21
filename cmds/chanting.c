
#include <xyj_x.h>
#include <ansi.h>

inherit F_CLEAN_UP;

#define PROP						"sitting"
#define DURATION					120			//����ʱ��
#define DX_GAIN						1100		//200 buddhism��1.0��/Сʱ��24��/��
#define	NORM_RATIO					100

int main(object me, string arg)
{
	object env = environment(me);
	int level = me->query_skill("buddhism") * 2;
	int dx_gain = DURATION * DX_GAIN * level / 3600 / 200;

	if(!env->query("jingzuo_room"))
		return notify_fail("�˴����˾���������\n");

	if(level < 20 ) 
		return notify_fail("��Ĵ�˷���Ϊ̫�ͣ������й�������\n");

	if(me->is_busy() || me->query_temp(PROP) || me->is_fighting())
		return notify_fail("��������æ���ء�\n");

	if(me->query("sen") < 100 ||  me->query("kee") < 100)
		return notify_fail("������״̬���ѣ���������Ҫ�߻���ħ��\n");

	if(me->query("water") < 10 )
		return notify_fail("�����ڿڸ��������ЪЪ�ɡ�\n");

	if( me->query("mana") < 50 )
		return notify_fail("�����ڷ���̫�ͣ���������Ҫ�߻���ħ��\n");

	message_vision(HIY "$Nϯ�ض�����˫Ŀ΢�գ��������������˾��ġ�\n" NOR, me);

	me->start_busy(DURATION / 2 + 1);
	me->set_temp(PROP, 1);
	call_out("finish", DURATION, me, dx_gain);
	return 1;
}

string* msg = ({
	"����Ϊ�࣬����ƣ�ͣ���̰����������Ϊ���������ڡ�",
	"и��׹�䣬���о������Ʒ��ն񣬴ݷ���ħ������������",
	"�޳����������������ѧ���ţ������ǻۣ��ɾͱ�ţ��̻�һ�У�Ϥ�Դ��֡�",
	"ƶ���Թ������Ե��������ʩ������Թ�ף�����ɶ񣬲������ˡ�",
	"������ȼ������������������ģ��ռ�һ�С�",
	"Ը���������������࣬�����������Ͼ����֡�",
	"Ը�Դ˹��£�ׯ�Ϸ������ϱ����ض����¼���;�ࡣ",
	"���м����ߣ�Ϥ�������ģ���������������������顣",
});

void finish(object me, int dx)
{
	int ratio = 100;
	mapping gains;
	
	if(!me) return;
	me->delete_temp(PROP);

	if(me->query("family/family_name") != "�Ϻ�����ɽ") ratio -= 30;
	if(me->query("class") != "bonze") ratio -= 30;
	if(me->query("betray/count")) ratio -= 30;

	dx = dx * ratio / 100;
	gains = ([ DEXP : dx, PEXP : dx / 4 ]);

	message_vision(HIY"$N���������" + msg[random(sizeof(msg))] + "\n"NOR, me);
	message_vision(HIY"$N���������۾�������һ����վ��������\n"NOR, me);

	//������
	if(TASK_EXC->do_reward(me, "�Լ�", "�о�", gains, NORM_RATIO)) {
		int point = dx / 2 * 20;
		me->add("daoxing", dx);
		me->add("potential", dx / 2);
		me->add("learned_points", dx / 2);
		me->improve_skill("buddhism", point, 1);
		
		tell_object(me, HIC"��ĵ���������" + chinese_number(dx*3) + "ʱ����\n"NOR);
		//tell_object(me, HIC"���Ǳ��������" + chinese_number(dx/4) + "�㣡\n"NOR);		
		tell_object(me, HIC"��Ĵ�˷�������" + chinese_number(point)+ "�㣡\n"NOR);

		me->add("mana", -20);
		me->add("water", -20);
		me->receive_damage("sen", 20);
		me->receive_damage("kee", 20);
	}
}

int help(object me)
{
	write(@HELP
ָ���ʽ : chanting

�о���������ߵ��С�
HELP
	   );
	return 1;
}


int test()
{
	main(this_player(), 0);
}

