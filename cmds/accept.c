

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object obj, env;

	if(!arg)
		return notify_fail("��Ҫ����˭�Ĺ������룿\n");

	if(arg == "none") {		
		me->set_temp("accept", 0);
		return notify_ok("OK.\n");
	}

	if(me->is_ghost())
		return notify_fail("���˹��ˣ�����ʵ��ɣ�\n");

	if(me->is_fighting() || me->is_busy())
		return notify_fail("���æ�����ܽ��ܹ������롣\n");

	obj = find_player(arg);
	if(!obj) obj = find_living(arg);    
	if(!obj) obj = LOGIN_D->find_body(arg);

	if(!obj) return notify_fail("û������ˡ�\n");

	if(wizardp(obj) && !wizardp(me)) return notify_fail("û������ˡ�\n");

	if(obj->query_temp("invite") != "public")
		return notify_fail(obj->query("name") + "���ڲ�û�й���������ˡ�\n");

	if( !wizardp(me) && userp(me) )
		if (env=environment(me))
			if(!env->query("outdoors"))
				return notify_fail("�㻹�ǵ�����ȥ����"+obj->query("name")+"������ɣ�\n");

	if( !wizardp(me) && userp(me) ){
		if( uptime()-me->query_temp("accept_time")<10)
			return notify_fail("���Ժ��ٽ�������ɡ�\n");

		me->set_temp("accept_time",uptime());
	}

	if (me->query_temp("accept") == obj->query("id"))
		return notify_fail("���Ѿ�����"+obj->query("name")+"�Ĺ��������ˡ�\n");

	if( !wizardp(me) && userp(me) ){
		if ((obj->query("id")=="zhenyuan_daxian")   && me->query("life/live_forever") )
			return notify_fail("���Ѿ������ֻ��ˣ����ǰѻ����������˰ɡ�\n");

		if ((obj->query("id")=="zhenyuan_daxian") && me->query("combat_exp") <=100000 ) 
			return notify_fail("��ı��»���������Ԫ���ɲ��������㡣\n");
	}
	tell_object (me,GRN"�����"GRN+obj->query("name")+NOR GRN"�Ĺ������롣\n"NOR);
	tell_object (obj, me->query("name")+GRN"���ڽ�����Ĺ������롣\n"NOR);

	me->set_temp("accept",obj->query("id"));
	return 1;
}

int help(object me)
{
write(@HELP

ָ���ʽ : accept <ĳ��> | none

���ָ����߱����������/���Ĺ������룬����ȡ�������������롣


HELP
    );
    return 1;
}

