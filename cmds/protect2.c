
#include <ansi.h>
#include <xyj_x.h>

inherit F_CLEAN_UP;

#define CD						30
#define DURATION				23		//��Լ2��


//����ĳ��[����]
int protect_sb(object me, object who, int with_life)
{
	int now = time();
	
	me->set_temp("protect", who);

	foreach(object ob in who->query_enemy()) {
		me->fight_ob(ob);
		ob->fight_ob(me);
	}

	if(!with_life) 
		message_vision(HIC"$N��ʼ����$n��\n"NOR, me, who);
	else {
		if(!cd_start(me, "protect", CD)) return notify_fail("�㲻������ƴ����\n");
		
		who->set_temp("protector", me);
		who->set_temp("protector_until", 1 + now + DURATION * SEC_PER_HB);
		tell_object(me, "��׼��������" + who->name() + "��\n");
	}
	return 1;
}

//�����˴�������
object stand_in(object me)
{
	object who = me->query_temp("protector");
	int until = me->query_temp("protector_until");

	if(until > time() && same_env(who, me) && can_move(who)) {
		message_vision("$N����һ�е���$n��ǰ��\n", who, me);
		who->start_busy(DURATION);
		return who;
	}
	return me;
}

int main(object me, string arg)
{
	object who;

	if(!arg) {
		who = me->query_temp("protect");
		if(who)	tell_object(me, "���������ڱ���" + who->name() + "��\n");
		else tell_object(me, "������û�б����κ��ˡ�\n");
	} 
	else if(arg == "none") {
		me->set_temp("protect", 0);
		return notify_ok("OK.\n");
	}
	else if(arg == "me" || arg == me->query("id"))  
		return notify_fail("��Ҫ����ʲô�ˣ�\n");
	else {
		int with_life = sscanf(arg, "-l %s", arg) == 1;

		who = present(arg, environment(me));

		if(!objectp(who))
			return notify_fail("��Ҫ����ʲô�ˣ�\n");

		if(!living(who))
			return notify_fail("�㲻�ܱ���" + who->name() + "��\n");

		if(me->is_fighting(who))
			return notify_fail("�㲻�ܱ���ս������\n");

		if(!userp(who) && who->query("owner") != me->query("id"))
			return notify_fail(who->name() + "�ܾ����㱣����\n");

		if(me->query_condition("no_pk_time") > 480)
			return notify_fail("�����ɱ��̫�ࡣ����\n");

		if(me->query("age") < 18)
			return notify_fail("����δ���ס�\n");

		return protect_sb(me, who, with_life);
	}
	
	return 1;

}

int help(object me)
{
   write( @HELP
ָ���ʽ: protect [-l] [<����>|<NPC>|none]

��ʼ��������������ĳ�ˡ���ѡ����-l��ʾ������Ŀ�ꡣ
HELP
   );
   return 1;
}
