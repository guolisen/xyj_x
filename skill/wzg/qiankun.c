
//weiqi, mon 1/98

#include <ansi.h>

inherit SSERVER;

#define WIND_FILE "/d/jjf/obj/wind_seal.c"

void get_out(object where);

int cast(object me, object target)
{
	string msg;
	int success, ap, dp;
	object sleeveroom,sleeve;
	string sname;
	object env, *inv;
	int size, i, taiyi_level;
	int maxenc;
	int cost;

	seteuid(getuid());

	if( me->query("spell_qiankun_on") != 1 )
		return notify_fail("�㻹��������Ǭ����\n");

	//	if( !target ) target = offensive_target(me);

	if(!target) {
		//see if I am fighting someone...this is useful for NPC...
		// this is only for NPC. -mon
		if(!userp(me) && (offensive_target(me)) ) 
			target = offensive_target(me);
		else {
			// then take stuff out.
			sleeveroom=load_object("/d/wiz/sleeveroom");
			if(!sleeveroom) return notify_fail("������ӿ������ˡ�\n");

			sname=me->query("id")+"'s sleeve";
			if(!sleeve=present(sname,sleeveroom)) {
				message_vision("$N������ӭ��һ˦����������ʲôҲû�С�\n",me);
				return 1;
			}

			size=sizeof(inv=all_inventory(sleeve));
			if(!size) {
				message_vision("$N������ӭ��һ˦����������ʲôҲû�С�\n",me);
				return 1;
			}

			msg="$N������ӭ��һ˦��";
			for(i=0;i<size;i++) {
				if(inv[i]->is_character())
					msg+="$n��ͨһ��ˤ���ڵ��ϡ�\n";
				else
					msg+="$n�̵�һ�����ڵ��ϡ�\n";

				env=environment(me);
				while(env && !(inv[i]->move(env))) env=environment(env);		//2010.11 fix bug

				message_vision(msg,me,inv[i]);
				msg="";	    
			}
			// added by xfile@bjxyj 2005-4-1
			// After player take the stuff out, the fabao sleeve is useless for
			// player, so it can be destructed here. if not, there was too many 
			// fabao sleeves resident in the memory, even the player quit game 
			// it was still there. and this will prevent the other player use "cast 
			// qiankun".	    
			if ( sleeve ) destruct( sleeve );	  
			return 1;
		}
	}

	if( !target
		|| !target->is_character()
		|| target->is_corpse()
		|| target==me)
		return notify_fail("��Ҫ��˭ʩչ����Ǭ����\n");

	//cost
	cost = 50 + target->query("mana_factor") * 4);	
	if(me->query("mana") < cost) return notify_fail("��ķ��������ˣ�\n");
	me->add("mana", -cost);


	msg =  HIR "$N�૵����˼������ͻȻ����һ�ӳ�$n���˹�ȥ��\n" NOR;
	message_vision(msg, me, target);

	if(!userp(target)) target->kill_ob(me);

	success = 1;
	ap = me->query("max_mana");
	dp = target->query("max_mana");
	if(ap < random(dp)) success = 0;
	//here we compared max_mana.
	//if the attacher has half of the max_mana of the target, 
	//he has 50% chance to success.

	if(success == 1 ) {

		sleeveroom=load_object("/d/wiz/sleeveroom");
		if(!sleeveroom) return notify_fail("������ӿ������ˡ�\n");

		sname=me->query("id")+"'s sleeve";
		if(!sleeve = present(sname,sleeveroom)) {
			sleeve = new("/d/obj/fabao/sleeve");
			if(!sleeve) return notify_fail("������ӿ������ˡ�\n");

			taiyi_level = me->query_skill("taiyi", 1);
			maxenc = taiyi_level * 2000;
			if(maxenc>400000) maxenc = 400000;
			sleeve->set_max_encumbrance(maxenc);
			//400000 correspondes to about 4 people?
			//note...if we want a npc can not be moved...can set its str very high...:)

			sleeve->set_name(me->query("name") + "��������", ({sname, "sleeve"}));
			sleeve->set("short", me->query("name") + "��������");
			if(!sleeve->move(sleeveroom)) return notify_fail("������ӿ������ˡ�\n");
		}

		if(target->move(sleeve)) {
			msg =  HIR "���ವ�һ��$n��װ�˽�ȥ��\n" NOR;
			message_vision(msg, me, target);

			// mon 7/31/98
			if(!userp(me)) {
				call_out("get_out", 120+random(240), sleeve);
			} else
				call_out("get_out", 240+random(480), sleeve);
			if(userp(target))
				call_out("get_out_user", 20, me, target, sleeve);


		} else {
			msg=HIR"���$nֻ��ҡ����һ�£��ֲ����ˡ�\n" NOR;
			msg+="$n��$N��˵̫���ˡ�\n";
			message_vision(msg, me, target);
		}

	} else  {
		msg =  HIR "�����$n����һ�ƣ������ס$N�Լ����Դ���\n" NOR;
		message_vision(msg, me, target);		
	} 

	return 3 + 4;
}

void get_out(object where)
{
	object wind, *inv;
	int i;

	if(!where) return;

	i=sizeof(inv=all_inventory(where));
	while(i--) {
		if(inv[i]->is_character()) { // NPC or players 
			wind=new(WIND_FILE); // wind can only be used once, so need to new.
			wind->do_blow(inv[i]);
			message_vision("ֻ������ǵش���һ�ӣ�$N��ͨһ���ݺݵ����ڵ��ϣ�\n",
				inv[i]);
			//         inv[i]->unconcious();
			//destruct(wind);
		} else  // objects.
			destruct(inv[i]); 
	}


	// xfile@bjxyj 2005-4-1
	// make the same chanage as above.
	destruct( where );
	return;
}

void get_out_user(object me, object target, object sleeve)
{
	if(!me || !target || !sleeve) return;
	else {
		object env = environment(target);
		if(env != sleeve) return;
		env = environment(me);
		if(target->move(env)) {
			message_vision(CYN"$n�κ����Ĵ�$N������˳�������ͨһ�����ڵ��ϣ�\n"NOR, me, target);
		}
	}
}