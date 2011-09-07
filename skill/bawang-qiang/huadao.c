//Created By Pkyou@DHXYII 2002/5/7
//大唐将军府霸王枪法之回马枪。
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

//       if(me->query("family/family_name") != "将军府"  || me->query("betray/count"))
//       return notify_fail("你是哪儿偷学来的武功，也想用回马枪?\n");
  
	   if(me->is_busy())
       return notify_fail("你正忙着呢！\n");
       extra = (me->query_skill("bawang-qiang",1) + me->query_skill("dodge",1))/2;
       if ( extra < 50) return notify_fail("你的枪法太差，还是省省吧！\n");
       if( !target ) target = offensive_target(me);
       if( !target
       ||      !target->is_character()
       ||      !me->is_fighting(target) )
                return notify_fail("你要使用回马枪戳自己吗？\n");
       if (me->query("force")<=500) return notify_fail("你内力不济，手脚发软，连枪都拿不稳。\n");
       if (me->query("sen")<=200) return notify_fail("你精神不集中，小心从马上摔下来！\n");

       map = me->query_skill_map();

        if( undefinedp(map["spear"]) ) 
                return notify_fail("你没有使用枪法。\n");
          if( map["spear"] != "bawang-qiang" )
                 return notify_fail("你并没有使用枪法\n");
        weapon = me->query_temp("weapon");      
        if( !objectp(weapon) || weapon->query("skill_type")!= "spear" )
                return notify_fail("你并没有使用枪法\n");
		if (me->query_temp("hmq_busy")) return notify_fail("诱敌之计不可滥用，否则没人会信了。\n");
        rir = target->query_skill("dodge",1);
        me->add("force",-300);
        me->add("sen",-50);
		if( !me->query_temp("ridee") )
        message_vision(YEL"$N挽了个枪花，一个翻身跃出战团，大喝：“今日休战”说完掉头便走。\n"NOR,me);
	    else 
			{
        message_vision(YEL"$N突然双腿猛的一夹马肚，俯身虚晃一枪，大喝：“今日休战”说完拍马便走。\n"NOR,me);
        extra = extra + (me->query_skill("dodge",1))/2;
			}
//        if (random(me->query("combat_exp")*(extra/15+1))>target->query("combat_exp")*(rir/30+1))
//changed by huadao.2010.07.24.
        if ((me->query("combat_exp")*(extra/15+1))/3+random((me->query("combat_exp")*(extra/15+1))*2/3)>target->query("combat_exp")*(rir/40+1))
//        if (random(me->query("combat_exp")*(extra/15+1))>target->query("combat_exp")*(rir/40+1))
        {
			 ini_damage_apply = me->query_temp("apply/damage");
             message_vision(CYN "$n浑然不知其中诡秘，果真迎头追了上去，冷不防$N突然仰面俯身回身急刺！
只见$N手中长枪连抖数下，犹如蛟龙闹海般自上而下刺向$n要害之处！\n" NOR,me,target);
        if ( extra > 250)
               {
          me->add_temp("apply/damage",150);
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          message_vision(CYN "$N以迅雷不及掩耳之势连抖五枪,$n目瞪口呆，心中大叫上当！\n" NOR,me,target);
               }  
             else if ( extra > 150)
              {
          me->add_temp("apply/damage",100);
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          message_vision(CYN "$N以迅雷不及掩耳之势连抖四枪,$n目瞪口呆，心中大叫上当！\n" NOR,me,target);
              } else if ( extra > 100)
             {
          me->add_temp("apply/damage",70);
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          message_vision(CYN "$N以迅雷不及掩耳之势连抖三枪,$n目瞪口呆，心中大叫上当！\n" NOR,me,target);
             } else
             {
          me->add_temp("apply/damage",50);
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          COMBAT_D->do_attack(me,target, me->query_temp("weapon"));  
          message_vision(CYN "$N以迅雷不及掩耳之势连抖二枪,$n目瞪口呆，心中大叫上当。\n" NOR,me,target);
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
          message_vision(WHT"但$N的攻势虽然凌厉，却招招落空，丝毫没有能对$n造成任何威胁。\n"NOR,me,target);
	    else 
			{
          message_vision(WHT"但$n轻松看破$N的诡计，并不上$N的当，反而一个翻身档在了$N的面前。\n"NOR,me,target);

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
