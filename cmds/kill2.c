// firefox 11/21/2009

inherit F_CLEAN_UP;

#include <xyj_x.h>
#include <ansi.h>
#include "/cmds/std/valid_kill.h"

#define PROTECT "/cmds/std/protect"

//��ɱ
void do_kill(object me, object obj)
{
	me->kill_ob(obj);
	if(!userp(obj) && !obj->accept_kill(me))
		obj->kill_ob(me);
	else if(!userp(me))
		obj->kill_ob(me);
	else {
		obj->kill_ob(me);
		tell_object(obj, HIR "�����Ҫ��" + me->name() 
			+ "�����ಫ������Ҳ���������һ�� kill ָ�\n" NOR);
	}

	//����
	foreach(object ob in PROTECT->gards(obj)) {
		message_vision(HIC"$N����ǰȥ��ס��$n��\n"NOR, ob, me);
		obj->kill_ob(me);
	}
}

int main(object me, string arg)
{
	if(!arg) {
		return notify_fail("����ɱ˭��\n");
		/*
		if(me->is_busy()) return notify_ok("��������æ���ء�\n");
		if(me->is_fighting()) return notify_ok("�����ڴ�ܣ��Թ˲�Ͼ��\n");

		me->remove_all_killer();
		write("������Ĭ��һ����"HIG"ˡ"NOR"���֣�һ��ԩ�������Ժ�\n");
		me->start_busy(10);*/
	} else {
		object env = environment(me);
		int for_guard = sscanf(arg, "-g %s", arg) == 1;
		object target = present(arg, env);
		string callname;

		if(env->query("no_fight")) return notify_fail("���ﲻ׼ս����\n");
		if(!objectp(target)) return notify_fail("����û������ˡ�\n");
		if(!BTL->can_attack(me, target)) return notify_fail("����ɱ˭��\n");
		if(!env->query("in_bg") && !valid_kill(me, target, 0)) return 0;
		
		callname = RANK_D->query_rude(target);

		if(!for_guard) {
			if(me->is_killing(target->query("id"))) {
				write("\n�����" + target->name() + "�ȵ�����" + callname + "�����ղ������������һ��\n\n");
			} else {
				message_vision("\n$N����$n�ȵ�����" + callname + "�����ղ������������һ��\n\n", me, target);				
			}
			do_kill(me, target);
			return 1;
		} else {
			foreach(object ob in GUARD->gards(me)) {
				do_kill(ob, target);
			}
			return notify_ok("OK.\n");
		}
	}
	return 1;
}

int help(object me)
{
  write(@HELP
ָ���ʽ : kill [-g] <����>
 
���ָ������������ʼ����һ��������ҡ���ɱ���Է���kill �� fight ����
��ͬ����˫�������浶ʵǹ�ش򶷣�Ҳ����˵����������ˡ����� kill ֻ�赥��
��һ����Ը�Ϳ��Գ������������κ���ʹ�� kill ָ��Ὺʼս����ͨ�����
�Է��� NPC �Ļ�������Ҳ��ͬ������ʹ�� kill������-g����ָʾ������

�����˶���ʹ�� kill ָ��ʱ����ֺ�ɫ�����������㣬����һ����Ҷ��ԣ����
��û�ж�һ������ʹ�ù� kill ָ��Ͳ��Ὣ�Է���Ĵ��˻�ɱ��( ʹ�÷�����
��)��

�������ָ��: fight

�й� fight �� kill �������뿴 'help combat'.
HELP
    );
    return 1;
}

