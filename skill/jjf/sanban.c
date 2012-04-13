
#include <xyj_x.h> 
#include <ansi.h>
 
inherit SSERVER;

#define NAME			"无敌三板斧"
#define MSG0			CYN"$N一声暴喝：开瓜！剔牙！掏耳朵！三招一气呵成！\n\n"NOR

mixed*	_msgs = ({
	({
		CYN"只见一道青影划过，大斧直劈$n顶门！\n"NOR,
		HIR"$n试图架开，但挡不住$N的来势，被震得吐出一口鲜血！\n"NOR,
		"$n轻轻一闪，大斧带着一阵劲风从身边斩下，但没伤到$n分毫。\n",
	}),
	({
		CYN"$N大斧已经带过，顺势以斧尾护手尖刀疾挑$n面门！\n"NOR,
		YEL"$n攻势已然发出，来不及回防，脸上被割掉一片皮，显然伤得不轻！\n"NOR,
		"$n脑袋微微一侧，避过了$N的攻势。\n",
	}),
	({
		CYN"$N迅疾无伦地翻转斧头，大斧向$n脑袋横劈过去！\n"NOR,
		WHT"$n眼见来势凌厉，企图低头避过，但不料大斧随着下劈，从$n背上割下一大片皮肉！\n"NOR,
		"$n不顾自身危险，中宫直进，向$N攻去，果然将来招化解了。\n",
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
		return notify_fail("无敌三板斧不是练着好看的，只能对战斗对手施用。\n");
	if(!BTL->require(me, NAME, req)) return 1;
	if(!cd_start(me, "sanban", 1)) return notify_fail("绝招用的太多太滥就不灵了。\n");
	
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
		int eff_kee = target->query("eff_kee");				//TODO:加入伤害限制
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



  msg = CYN"$N一声暴喝：开瓜！剔牙！掏耳朵！三招一气呵成！\n\n只见一道青影划过，大斧直劈$n顶门！\n"NOR;
  if( random(mylev+targetlev+mystr*3+targetstr*3) > (targetlev+targetstr*3))
    {
      msg += hitone[random(sizeof(hitone))];
      success+=1;
      if() hurt+=1;
      damage=15+random(mykar/3);
    }
  else msg+=missone[random(sizeof(missone))];
  msg+=CYN"\n$N大斧已经带过，顺势以斧尾护手尖刀疾挑$n面门！\n"NOR;
  if( random(myexp+targetexp+mylev+targetlev) > (targetexp+targetlev))
    {
      msg += hittwo[random(sizeof(hittwo))];
      success+=1;
      if(random(mykar+targetkar)>targetkar) hurt+=1;
      damage+=15+random(mykar/3);
    }
  else msg+=misstwo[random(sizeof(misstwo))];
  msg+=CYN"\n$N迅疾无伦地翻转斧头，大斧向$n脑袋横劈过去！\n"NOR;
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
