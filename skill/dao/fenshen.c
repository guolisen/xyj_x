// fenshen.c ������

inherit SSERVER;

#include <xyj_x.h>

#define CD			20
#define FENSHEN		"/obj/npc/jiashen"

int cast(object me, object target)
{
	object soldier;
	mapping db, tdb;
	int dao = me->query_skill("dao", 1);
	int cost = 10 + dao;

	if(!me->is_fighting())
		return notify_ok("ֻ��ս���в���ʹ�÷�����\n");	

	if(me->query("mana") < cost)
		return notify_ok("��ķ��������ˣ�\n");

	if(!cd_start(me, "invoke", CD)) 
		return notify_ok("��ոշֹ����ٷ����Σ�գ�\n");

	message_vision("$N�૵����˼������\n", me);

	me->add("mana", -cost);

	seteuid(getuid());
	soldier = new(FENSHEN);
	db = soldier->query_entire_dbase();
	tdb = soldier->query_entire_temp_dbase();
	
	//�Ի����
	tdb["apply/short"] = ({ me->short() });
	tdb["invoker"] = me;

	copy_name_id(me, soldier);
	soldier->move(environment(me));
	soldier->invocation(me);	
	soldier->set_leader(me);	

	//���� & ״̬	
	db["chat_chance_combat"] = 30;
	db["chat_msg_combat"] = ({
		(: call_other, soldier, "perform_action", "stick", "qiankun" :),
		(: call_other, soldier, "perform_action", "stick", "qiankun" :),
		(: call_other, soldier, "cast_spell", "dingshen" :),
	});
	db["cps"] = 1;								//�����޶���	
	db[CEXP] = (db[CEXP] + db[DEXP]) / 2;		//�������û�

	SKI->set_level(soldier, dao);
	soldier->reset_action();
	
	if(!me->query("betray/count")) {
		int enhance = dao / 2;
		tdb["apply/attack"] += enhance;
		tdb["apply/defense"] += enhance;
	}

	return 1;
}
