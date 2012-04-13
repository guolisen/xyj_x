
#include <xyj_x.h> 
#include <ansi.h>
 
inherit SSERVER;

#define NAME			"�޵����師"
#define MSG0			CYN"$Nһ�����ȣ����ϣ��������Ͷ��䣡����һ���ǳɣ�\n\n"NOR

mixed*	_msgs = ({
	({
		CYN"ֻ��һ����Ӱ��������ֱ��$n���ţ�\n"NOR,
		HIR"$n��ͼ�ܿ���������ס$N�����ƣ�������³�һ����Ѫ��\n"NOR,
		"$n����һ�����󸫴���һ�󾢷�����ն�£���û�˵�$n�ֺ���\n",
	}),
	({
		CYN"$N���Ѿ�������˳���Ը�β���ּ⵶����$n���ţ�\n"NOR,
		YEL"$n������Ȼ�������������ط������ϱ����һƬƤ����Ȼ�˵ò��ᣡ\n"NOR,
		"$n�Դ�΢΢һ�࣬�ܹ���$N�Ĺ��ơ�\n",
	}),
	({
		CYN"$NѸ�����׵ط�ת��ͷ������$n�Դ�������ȥ��\n"NOR,
		WHT"$n�ۼ�������������ͼ��ͷ�ܹ��������ϴ�������������$n���ϸ���һ��ƬƤ�⣡\n"NOR,
		"$n��������Σ�գ��й�ֱ������$N��ȥ����Ȼ�����л����ˡ�\n",
	}),
});

int perform(object me, object target)
{
	int cost = me->query("force_factor") * 3;
	int success = 0, hurt = 0, damage = 0;
	int kar0, kar1;
	
	mapping req = ([
		"skill1"	: ([ "sanban-axe" : 100, "lengquan-force" : 100 ]),
		"prop"		: ([ "force" : cost ]),
		"skill_map"	: ([ "force" : "lengquan-force" ]);
	]);
	mapping cmp_parm = ([
		"prop"			: ([ CEXP : 1, "force_factor" : 1 ]),
		"skill"			: ([ "unarmed" : 3 ]),
		"skill_pair"	: ([ ({"axe", "parry"}) : 3]),
	]);

	target = BTL->get_victim(me, target);

	if(!target || !me->is_fighting(target))
		return notify_fail("�޵����師�������źÿ��ģ�ֻ�ܶ�ս������ʩ�á�\n");
	if(!BTL->require(me, NAME, req)) return 1;
	if(!cd_start(me, "sanban", 1)) return notify_fail("�����õ�̫��̫�ľͲ����ˡ�\n");
	
	BTL->pay(me, req["prop"]);
	msv(MSG0, me, target);

	kar0 = me->query_kar();
	kar1 = target->query_kar();
	foreach(string* arr in _msgs) {
		msv(arr[0], me, target);
		if(BTL->cmp_random20(me, target, cmp_parm) > 85) {
			msv(arr[1], me, target);
			success++;
			if(random(kar0 + kar1) > kar1) hurt++;
			damage += 15 + random(kar0 / 3);
		} else {
			msv(arr[2], me, target);
		}
	}
	if(success) {		
		int eff_kee = target->query("eff_kee");				//TODO:�����˺�����
		int kee = target->query("kee");		
		hurt = damage * hurt / success;

		target->receive_wound("kee", eff_kee * hurt / 100, me);
		target->receive_damage("kee", kee * (damage - hurt) / 100, me);
		me->start_busy(1);
	} else {
		msv(MSG2, me, target);		
	}
	BTL->fight_enemy(target, me);
	return 2;
}




  string msg,targetrude;
  int success,hurt,diff,damage;
  int myexp=(int)me->query("combat_exp")/5000;
  int mylev=(int)me->query_skill("axe");
  int mystr=(int)me->query("str")+(int)(me->query_skill("unarmed")/10-2);
  int mykar=(int)me->query_kar();
  int targetlev, targetstr,targetkar,targetexp,targeteffkee;

  string *miss;

  targetrude=RANK_D->query_self_rude(target);
  targetexp=(int)target->query("combat_exp")/5000;
  targetlev=(int)target->query_skill("parry");
  targetstr=(int)target->query("str")+(int)(target->query_skill("unarmed")/10-2);
  targetkar=(int)target->query_kar();



  msg = CYN"$Nһ�����ȣ����ϣ��������Ͷ��䣡����һ���ǳɣ�\n\nֻ��һ����Ӱ��������ֱ��$n���ţ�\n"NOR;
  if( random(mylev+targetlev+mystr*3+targetstr*3) > (targetlev+targetstr*3))
    {
      msg += hitone[random(sizeof(hitone))];
      success+=1;
      if() hurt+=1;
      damage=15+random(mykar/3);
    }
  else msg+=missone[random(sizeof(missone))];
  msg+=CYN"\n$N���Ѿ�������˳���Ը�β���ּ⵶����$n���ţ�\n"NOR;
  if( random(myexp+targetexp+mylev+targetlev) > (targetexp+targetlev))
    {
      msg += hittwo[random(sizeof(hittwo))];
      success+=1;
      if(random(mykar+targetkar)>targetkar) hurt+=1;
      damage+=15+random(mykar/3);
    }
  else msg+=misstwo[random(sizeof(misstwo))];
  msg+=CYN"\n$NѸ�����׵ط�ת��ͷ������$n�Դ�������ȥ��\n"NOR;
  if(random(myexp+targetexp+mykar*10+targetkar*10)>(targetexp+targetkar))
    {
      msg+=hitthree[random(sizeof(hitthree))];
      success+=1;
      if(random(mykar+targetkar)>targetkar) hurt+=1;
      damage+=15+random(mykar/3);
    }
  else msg+=missthree[random(sizeof(missthree))];
  diff=3-success;
  if (diff<0) diff = 0;
  if (success) hurt=damage*hurt/success;
  else hurt=0;
  me->add("force", -(150*success+70*diff));
  targeteffkee=(int)target->query("eff_kee");
  target->receive_wound("kee", targeteffkee*hurt/100);
  target->receive_damage("kee", target->query("kee")*(damage-hurt)/100);
  if(success)
    {
      me->start_busy(1+random(4-(mykar+5)/10));
      msg+=hit[random(sizeof(hit))];
    }
  else
    {
      me->start_busy(random(4-(mykar+5)/10));
      msg+=miss[random(sizeof(miss))];
    }
  message_vision(msg, me, target);
  return 1;
}
