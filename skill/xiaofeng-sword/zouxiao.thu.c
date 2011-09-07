// cracked by vikee 2/09/2002   vikee@263.net
// zouxiao.c  ���ﴫ��  

#include <ansi.h>
inherit SSERVER;

#define PFM_ID		"zouxiao"
#define PFM_DELAY	6

string* skills = ({"zouxiao", "qin", "literate"});

//����skillƽ��ֵ
int avg_skill(object who, string* list)
{
	int n = sizeof(list);
	int sum = 0;
	foreach(string skill in list) {
		sum += who->query_skill(skill, 1);
	}
	return n ? sum / n : 0;
}

int perform(object me, object target)
{
	string msg;
	int damage, ap, dp,qixue,eff_qi,max_qi,qi_pcg;
	object weapon = me->query_temp("weapon");

	if( !target ) target = offensive_target(me);

	if( !target
		||      !target->is_character()
		||      target->is_corpse()
		||      target==me)
		return notify_fail("��Ҫ��˭���\n");

	if (me->query_temp(PFM_ID"_busy")>time()) return notify_fail("�����õ�̫��̫�ľͲ����ˡ�\n");

	if( !me->is_fighting(target) || target->is_busy() )
		return notify_fail("��Ҷ���æ��û����ʱ�����㴵�����\n");

	if (!weapon || weapon->query("music/type") != "xiao")
		return notify_fail("������ļһﴵ�������ӡ�\n");

	if (me->query_skill_mapped("force")!="zhenyuan-force")
		return notify_fail("ֻ������Ԫ�񹦲����������\n");

	if (me->query_skill("xiaofeng-sword",1)<50)
		return notify_fail("���������½�������������\n");

	if (me->query_skill("zouxiao",1)<60)
		return notify_fail("������Ĺ��򻹲������ٺú������ɡ�\n");

	if((int)me->query("force") < 200 )
		return notify_fail("����������������\n");

	if((int)me->query("kee") < 200 )
		return notify_fail("��������Ѿ������ˣ�\n");

	if((int)me->query("sen") < 200 )
		return notify_fail("���޷����о�����\n");

	msg = HIC "\n$N����"+weapon->query("name")+HIW"������$n������һ��������������"
		+"����̾Ϣ�����ƿ���������\n��������������ɪɪɪ����֮��������һ�ε�С��������Ҷ��\n" NOR,

	me->add("sen", -150);
	me->add("kee", -150);
	me->add("force", -150);

	ap = 2 * avg_skill(me, ({"xiaofeng-sword"}) + skills);
	damage = ap * ap / 300;
	ap = ap * 3 + pow((int)me->query("combat_exp"), 0.333);
	
	dp = 2 * avg_skill(target, ({"spells"}) + skills);
	dp = dp * 3 + pow((int)target->query("combat_exp"), 0.333);

	if( random(100*ap/dp) <  5 ) 
	{
		msg += HIW "$n������������Ц��������㱾�£�Ҳ����Ц�󷽣�"
			+"$N��ʱ�����ѵ���\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(2);	//ʧ�ܴ���̫���Ǻܶ༼�ܷϵ���ԭ��
	} 
	else if( random(100*ap/dp) <  50 ) 
	{
		msg += HIW "��$n������ţ���Ϊ������\n"NOR;
		message_vision(msg, me, target);
		me->start_busy(1);
	}
	else 
	{
		DAMAGE_D->bring_damage(target, "sen", damage, "magic", "spells", me);
		//target->receive_damage("sen",damage,me);
		msg += HIW "$n��������������Ī������ĸе�һ�������������������ˮ�������¡�\n"NOR;
		message_vision(msg, me, target);
		COMBAT_D->report_sen_status(target);
		target->start_busy(3);
		me->start_busy(1);
		if(!random(3)) me->improve_skill("zouxiao", 1);
	}
	target->kill_ob(me);
	
	me->set_temp(PFM_ID"_busy", time() + PFM_DELAY );
	return 1;
}
