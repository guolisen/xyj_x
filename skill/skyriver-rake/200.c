// by firefox 02/09/2010

inherit SSERVER;

#include <xyj_x.h>
#include <ansi.h>

int perform(object me, object target)
{
	target = BTL->get_victim(me, target);
	if(!target) return notify_ok("��˭��\n");

	message_vision(HIW"\n$N����չ��,�·�ˮ��һ���趯�����а�,������������۷�����ٰңݣ�\n\n"NOR,me,target);
	
	for(int i = 1; i < 12; ++i) {
		message_vision(HIC"$N��ͼʹ��[������ٰ�]�ģ۵�"+chinese_number(i)+"�ңݣ����Ǳ����ִ���ˣ�\n"NOR, me, target);
	}
	message_vision("......\n\n", me);
	for(int i = 198; i < 201; ++i) {
		message_vision(HIC"$N��ͼʹ��[������ٰ�]�ģ۵�"+chinese_number(i)+"�ңݣ����Ǳ����ִ���ˣ�\n"NOR, me, target);
	}

	message_vision(HIY"\n$N�����ñ�,ͣ������,��ΧҲ��ʱ�ָ���ƽ��.$nȴ��Ȼ��������.\n\n"NOR, me, target);
	me->command("haha " + target->query("id"));
	me->command("say С��������������㣬��ҲҪflood���㡣");
	me->start_busy(3);
	if(!target->is_busy()) target->start_busy(3);
	return 1;
}





