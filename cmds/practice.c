// cracked by vikee 2/09/2002   vikee@263.net
// practice.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string spe_skill, skill_name;
	int skill, skill_basic;
	int time = 1;

	seteuid(getuid());

	if(arg) {
		if(sscanf(arg, "%s for max", arg) == 1)
			time = 100;
		else if(sscanf(arg, "%s for %d", arg, time) != 2 ) 
			time = 1;
	}

	if(time > 50) time = 50;

	if( environment(me)->query("no_fight") || 
		environment(me)->query("no_magic") )
		return notify_fail("���ﲻ�������ĵط���\n");

	if( me->is_fighting() )
		return notify_fail("���Ѿ���ս�����ˣ�ѧһ��ʵս����ɡ�\n");

	if( me->is_busy() )
		return notify_fail("�����ں�æ��������ϰ��\n");

	if( !arg ) return (__DIR__"enable")->main(me, arg);

	if( !stringp(spe_skill = me->query_skill_mapped(arg)) )
		return notify_fail("��ֻ����ϰ�� enable ָ�������⼼�ܡ�\n");

	skill_basic = me->query_skill(arg, 1);
	skill = me->query_skill(spe_skill, 1);

	if( skill < 1 )
		return notify_fail("�����û��ѧ�᡹����ܰɣ������ȥ��̱��ˡ�\n");
	if( skill_basic < 1 )
		return notify_fail("����ⷽ��ļ��ܻ���һ�ϲ�ͨ����ô��ȴӻ���ѧ��\n");

	if( skill*skill*skill/10 > (int)me->query("combat_exp") )
		return notify_fail("�����ѧ��Ϊ��û��������磬�����ٶ�Ҳû�á�\n");
	//note, if a magic skill can also be practiced...need change this.

	notify_fail("�����ڲ�����ϰ����ܡ�\n");
	if( !SKILL_D(spe_skill)->valid_learn(me) ) return 0;

	// mon 10/19/98
	//if(MISC_D->random_capture(me,20000,0)) return 1;

	skill_name = to_chinese(spe_skill);

	notify_fail("��������ϰ" + skill_name + "�����ǲ�û���κν�����\n");

	if(skill_basic <= skill && !random(100))
		write("���" + skill_name + "��������ˣ���������ʦ�������̰ɣ�\n");

	message_vision("$N������ѧ��ϰ��" + skill_name + "��\n", me);

	for(int i = 0; i < time; ++i) {
		if( SKILL_D(spe_skill)->practice_skill(me) ) {
			me->improve_skill(spe_skill, 2 * skill_basic/5 +1, skill_basic > skill? 0: 1);						
		} else {
			return 0;
		}
	}
	//write( HIY "���" + skillname + "�����ˣ�\n" NOR);

	return 1;
}

int help(object me)
{
	write(@TEXT
ָ���ʽ��practice <��������> [for <����>|max]

���ָ��������ϰĳ������ļ��ܣ�������ܱ����Ǿ��� enable ��רҵ���ܡ�

��������Ļ��������㹻�ߣ����Ծ�����ϰֱ����������������������ֻ��
��������ܵĵȼ��йأ����仰˵���ڼ���ϰ��ʹ�����ѧ���������ʤ������
��Ψһ;������Ȼ������֮ǰ������ʵ�������л���㹻�ľ�����������Ļ�
�����ܡ�
TEXT
		);
	return 1;
}
