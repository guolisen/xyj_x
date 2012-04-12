// zouxiao.c  ���ﴫ��  

#include <xyj_x.h>

#include <ansi.h>
inherit SSERVER;

#define CD				8

int perform(object me, object target)
{
	object weapon = me->query_temp("weapon");    
	
	int cost = me->query_skill("spells") / 2;
	int damage, ap, dp, ratio;

	if( !target ) target = offensive_target(me);

	if( !target
		||      !target->is_character()
		||      target->is_corpse()
		||      target==me)
		return notify_fail("��Ҫ��˭���\n");

	if (!weapon || weapon->query("music/type") != "xiao")
		return notify_fail("������ļһﴵ�������ӡ�\n");

	if (me->query_skill_mapped("force")!="zhenyuan-force")
		return notify_fail("ֻ������Ԫ�񹦲����������\n");

	if (me->query_skill("xiaofeng-sword",1)<50)
		return notify_fail("���������½�������������\n");

	if (me->query_skill("zouxiao",1)<60)
		return notify_fail("������Ĺ��򻹲������ٺú������ɡ�\n");

	if (target->query_skill("literate",1)<50)
		return notify_fail("��������������ţ�����ء�\n");

	if(me->query("force") < 500 )
		return notify_fail("����������������\n");

	if(!cd_start(me, "im_pfm", CD))
		return notify_fail("�������þͲ����ˣ�\n");

	me->add("force", -cost);

	ap = (me->query_skill("xiaofeng-sword", 1)
		+ me->query_skill("zouxiao", 1)
		+ me->query_skill("literate")) / 2;
	
	dp = (target->query_skill("literate")
		+ target->query_skill("spells")) / 2;

	damage = ap * 2;

	ap += pow(me->query("daoxing") * 1, 0.333);
	dp += pow(target->query("daoxing") * 1, 0.333);

	dp = dp > 1 ? dp : 1;
	ratio = ap * 100 / dp;
	trace(sprintf("%s ap=%d dp=%d ratio=%d damage=%d", getuid(me), ap, dp, ratio, damage));
	ratio += random(41) - 20;

	message_vision(HIM"$N����$n������һ������������������һ�ε�С��������Ҷ��\n"NOR, me, target);

	if(ratio < 90) {
		message_vision(YEL"��$n������ţ���Ϊ������\n"NOR, me, target);
	} else {	
		message_vision(HIG"$n��������������Ī������ĸе�һ�������������������ˮ�������¡�\n"NOR, me, target);
		target->receive_damage("sen", damage, me);
		target->receive_wound("sen", damage / 4, me);
		COMBAT_D->report_sen_status(target);
	}
	target->kill_ob(me);

	return 1;
}

