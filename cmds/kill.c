// by firefox 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>

int main(object me, string arg)
{
	if(!arg) {
		if(me->is_busy()) return notify_ok("��������æ���ء�\n");
		if(me->is_fighting()) return notify_ok("�����ڴ�ܣ��Թ˲�Ͼ��\n");

		me->remove_all_killer();
		write("������Ĭ��һ����"HIG"ˡ"NOR"���֣�һ��ԩ�������Ժ�\n");
		me->start_busy(10);
	} else {
		object target = present(arg, environment(me));
		string callname;
		if(environment(me)->query("no_fight")) return notify_fail("���ﲻ׼ս����\n");
		if(!objectp(target)) return notify_fail("����û������ˡ�\n");
		if(!BTL->can_attack(me, target)) return notify_fail("����ɱ˭��\n");
		
		callname = RANK_D->query_rude(target);
		if(me->is_killing(target->query("id"))) {
			write("\n�����" + target->name() + "�ȵ�����" + callname + "�����ղ������������һ��\n\n");
			me->kill_ob(target);
			return 1;
		}
		message_vision("\n$N����$n�ȵ�����"
			+ callname + "�����ղ������������һ��\n\n", me, target);

		if(target->query_temp("protected")) {
			object guard = present(target->query_temp("protect_ob"), environment(target));
			if(objectp(guard) && guard != me
				&& guard->query_temp("protect") == target->query("id"))
			{
				message_vision(HIC"$N����$n����˵�������ڴˣ����õ��ģ�\n"NOR, guard, target);
				message_vision(HIC"$N����ǰȥ��ס��$n�Ĺ�����\n"NOR, guard, me);
				guard->kill_ob(me);
				me->kill_ob(guard);
			}
		}
		me->kill_ob(target);
		if(userp(target)) target->fight_ob(me);
		else target->kill_ob(me);
	}
	return 1;
}

int help(object me)
{
  write(@HELP
ָ���ʽ : kill <����>
 
���ָ������������ʼ����һ��������ҡ���ɱ���Է���kill �� fight ����
��ͬ����˫�������浶ʵǹ�ش򶷣�Ҳ����˵����������ˡ����� kill ֻ�赥��
��һ����Ը�Ϳ��Գ������������κ���ʹ�� kill ָ��Ὺʼս����ͨ�����
�Է��� NPC �Ļ�������Ҳ��ͬ������ʹ�� kill��

�����˶���ʹ�� kill ָ��ʱ����ֺ�ɫ�����������㣬����һ����Ҷ��ԣ����
��û�ж�һ������ʹ�ù� kill ָ��Ͳ��Ὣ�Է���Ĵ��˻�ɱ��( ʹ�÷�����
��)��

�������ָ��: fight

�й� fight �� kill �������뿴 'help combat'.
HELP
    );
    return 1;
}

