//��Ůɢ�� 
// dream 7/17/97
// modified by xlb 11/98
//20100628 change for perform flower,by huadao.
#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        string msg;
        int damage, ap, dp;
//        int number, size, i, four,amount;
//        object *tar;
		object flowers;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ����Ůɢ������\n");

        if((int)me->query("force") < 25+(int)me->query("force_factor") )
                return notify_fail("�������������\n");
        if((int)me->query("kee") < 100 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");

        if((int)me->query_skill("baihua-zhang", 1) <80)
                return notify_fail("��İٻ��Ƽ��𻹲�����\n");
/*
        tar=all_inventory(me);
        size = sizeof(tar); 
        if(size) {
                for(i=0;i<size;i++)
                if(tar[i]->query("material") == "flower") {
                        if (tar[i]->query_amount())
                              number+=tar[i]->query_amount();
                        else number++;
                }
        }
        write((string)number+"\n");

		if((int)number < 5)
                return notify_fail("��Ļ�������ʩչ����Ůɢ������\n");
*/
        if( !flowers=present("ice rose", me) )
                return notify_fail("û�б���õ�������ʩչ�ó�����Ůɢ������\n");

		if (me->query_temp("moon_pfm_busy")) return notify_fail("���Ժ������ʹ����Ůɢ������\n");

        me->add("force", -125-(int)me->query("force_factor"));
        me->receive_damage("kee", 100);
        msg = HIC
"\n$N΢΢һЦ��������ն����������컨�꣬һʱ��������\n"+
"$nֻ����������Ӱ��ס�ˣ�һʱ��Ȼ��֪����мܣ�������˵�����ˣ�\n" NOR;

        ap = me->query_skill("baihua-zhang", 1);
// + me->query_skill("parry");
        ap = ( ap * ap * ap / (4 * 400) );
// + (int)me->query("kee");
        ap = ap*250 + (int)me->query("combat_exp");
        dp = target->query_skill("parry");
        dp = ( dp * dp * dp / (4 * 400) );
// + (int)target->query("kee");
        dp = dp*250 + target->query("combat_exp"); 
        if( random((ap + dp)/1000+1) <  dp/1000 ) {
                msg += HIC "˭֪$n��������ʤ������һ�ڣ��ѽ����л�����䣡\n\n"NOR;
                message_vision(msg, me, target);
        } else {
                damage = (int)me->query_skill("baihua-zhang",1) / 10 +
                        (int)me->query("sen") / 400 + random((int)me->query("sen") / 200 ) +
                        (int)me->query("kee") / 400 + random((int)me->query("kee") / 200 );
                msg += HIC "��Щ���꿴������������ȴ�缲�����������$n,�����Ƕ�����\n" NOR;
//                if (number < 10) damage = damage *  (random(number+1)/5);
//                else damage = damage * (random(10)/5);
					if (damage >100) damage = 100;
					if (damage < 50) damage = 50;

                if (random(10) == 0) damage = damage *  ((5+random(5))/5);
                else damage = damage * ((1+random(9))/5);
                        target->receive_damage("sen", me->query("eff_sen")*damage/100, me);
                        target->receive_damage("kee", me->query("eff_kee")*damage/70, me);
                        me->improve_skill("baihua-zhang", 1, 1);
                message_vision(msg, me, target);
                COMBAT_D->report_status(target);
         }


        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }
/*        
        for (i = 0; i< size; i++){
           if (tar[i]->query("material") == "flower"){
                amount=tar[i]->query_amount();
                if (amount) four+=amount;
                  else four++;
                if (four <= 5)
                destruct(tar[i]);
                else {
                       tar[i]->set_amount(four-5);
                       four=5;
                       break;
                }
           }
        }
*/
//      me->start_busy(3);
		me->set_temp("moon_pfm_busy",1);
		call_out("remove_effect",1+random(3),me);
        return 1;
}

void remove_effect(object me) {
  if (me)  me->delete_temp("moon_pfm_busy");
}
