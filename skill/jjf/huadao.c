//Created By Pkyou@DHXYII 2002/5/7
//���ƽ���������ǹ��֮����ǹ��
//modify by huadao .2010.07.24
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
//nosave object *enemy = ({});
int perform(object me, object target)
{                             
       int extra;
       int rir;
       int ini_damage_apply;
	   int mykar=(int)me->query_kar();
       mapping map;
       object weapon;
        object ridee;
         ridee=me->ride();

//       if(me->query("family/family_name") != "������"  || me->query("betray/count"))
//       return notify_fail("�����Ķ�͵ѧ�����书��Ҳ���û���ǹ?\n");
  
	   if(me->is_busy())
       return notify_fail("����æ���أ�\n");
       extra = (me->query_skill("bawang-qiang",1) + me->query_skill("dodge",1))/2;
       if ( extra < 50) return notify_fail("���ǹ��̫�����ʡʡ�ɣ�\n");
       if( !target ) target = offensive_target(me);
       if( !target
       ||      !target->is_character()
       ||      !me->is_fighting(target) )
                return notify_fail("��Ҫʹ�û���ǹ���Լ���\n");
       if (me->query("force")<=500) return notify_fail("���������ã��ֽŷ�����ǹ���ò��ȡ�\n");
       if (me->query("sen")<=200) return notify_fail("�㾫�񲻼��У�С�Ĵ�����ˤ������\n");

       map = me->query_skill_map();

        if( undefinedp(map["spear"]) ) 
                return notify_fail("��û��ʹ��ǹ����\n");
          if( map["spear"] != "bawang-qiang" )
                 return notify_fail("�㲢û��ʹ��ǹ��\n");
        weapon = me->query_temp("weapon");      
        if( !objectp(weapon) || weapon->query("skill_type")!= "spear" )
                return notify_fail("�㲢û��ʹ��ǹ��\n");
		if (me->query_temp("hmq_busy")) return notify_fail("�յ�֮�Ʋ������ã�����û�˻����ˡ�\n");
        rir = target->query_skill("dodge",1);
        me->add("force",-300);
        me->add("sen",-50);
		if( !me->query_temp("ridee") )
        message_vision(YEL"$N���˸�ǹ����һ������Ծ��ս�ţ���ȣ���������ս��˵���ͷ���ߡ�\n"NOR,me);
	    else 
			{
        message_vision(YEL"$NͻȻ˫���͵�һ����ǣ��������һǹ����ȣ���������ս��˵��������ߡ�\n"NOR,me);
        extra = extra + (me->query_skill("dodge",1))/2;
			}
//        if (random(me->query("combat_exp")*(extra/15+1))>target->query("combat_exp")*(rir/30+1))
//changed by huadao.2010.07.24.
        if ((me->query("combat_exp")*(extra/15+1))/3+random((me->query("combat_exp")*(extra/15+1))*2/3)>target->query("combat_exp")*(rir/40+1))
//        if (random(me->query("combat_exp")*(extra/15+1))>target->query("combat_exp")*(rir/40+1))
        {
			 ini_damage_apply = me->query_temp("apply/damage");
             message_vision(CYN "$n��Ȼ��֪���й��أ�����ӭͷ׷����ȥ���䲻��$NͻȻ���温������̣�
ֻ��$N���г�ǹ�������£����������ֺ������϶��´���$nҪ��֮����\n" NOR,me,target);
        if ( extra > 250)
               {
          me->add_temp("apply/damage",150);
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          message_vision(CYN "$N��Ѹ�ײ����ڶ�֮��������ǹ,$nĿ�ɿڴ������д���ϵ���\n" NOR,me,target);
               }  
             else if ( extra > 150)
              {
          me->add_temp("apply/damage",100);
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          message_vision(CYN "$N��Ѹ�ײ����ڶ�֮��������ǹ,$nĿ�ɿڴ������д���ϵ���\n" NOR,me,target);
              } else if ( extra > 100)
             {
          me->add_temp("apply/damage",70);
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          message_vision(CYN "$N��Ѹ�ײ����ڶ�֮��������ǹ,$nĿ�ɿڴ������д���ϵ���\n" NOR,me,target);
             } else
             {
          me->add_temp("apply/damage",50);
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          message_vision(CYN "$N��Ѹ�ײ����ڶ�֮��������ǹ,$nĿ�ɿڴ������д���ϵ���\n" NOR,me,target);
             }
          target->receive_damage("kee",0,me);
          target->start_busy(4);
		  me->set_temp("hmq_busy",1);
          me->set_temp("apply/damage",ini_damage_apply);
		  call_out("remove_effect",3+random(5),me);
        }
        else
        {

		  if( !living(target) )
          message_vision(WHT"��$N�Ĺ�����Ȼ������ȴ������գ�˿��û���ܶ�$n����κ���в��\n"NOR,me,target);
	    else 
			{
          message_vision(WHT"��$n���ɿ���$N�Ĺ�ƣ�������$N�ĵ�������һ����������$N����ǰ��\n"NOR,me,target);

		  if (random(3) == 0)
		  {
		  weapon = target->query_temp("weapon");
          COMBAT_D->do_attack(target,me,weapon);
		  };
			}
		  me->set_temp("hmq_busy",1);
//          me->start_busy(2);

		  me->start_busy(random(4-(mykar+5)/10));
		  call_out("remove_effect",10+random(5),me);
        }
        return 1;
}

void remove_effect(object me) {
  if (!me) return;
  me->delete_temp("hmq_busy");
}
