// fenshen.c 分身术

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
		return notify_ok("只有战斗中才能使用分身法！\n");	

	if(me->query("mana") < cost)
		return notify_ok("你的法力不够了！\n");

	if(!cd_start(me, "invoke", CD)) 
		return notify_ok("你刚刚分过身，再分身很危险！\n");

	message_vision("$N喃喃地念了几句咒语。\n", me);

	me->add("mana", -cost);

	seteuid(getuid());
	soldier = new(FENSHEN);
	db = soldier->query_entire_dbase();
	tdb = soldier->query_entire_temp_dbase();
	
	//迷惑敌人
	tdb["apply/short"] = ({ me->short() });
	tdb["invoker"] = me;

	copy_name_id(me, soldier);
	soldier->move(environment(me));
	soldier->invocation(me);	
	soldier->set_leader(me);	

	//技能 & 状态	
	db["chat_chance_combat"] = 30;
	db["chat_msg_combat"] = ({
		(: call_other, soldier, "perform_action", "stick", "qiankun" :),
		(: call_other, soldier, "perform_action", "stick", "qiankun" :),
		(: call_other, soldier, "cast_spell", "dingshen" :),
	});
	db["cps"] = 1;								//傀儡无定力	
	db[CEXP] = (db[CEXP] + db[DEXP]) / 2;		//道行所幻化

	SKI->set_level(soldier, dao);
	soldier->reset_action();
	
	if(!me->query("betray/count")) {
		int enhance = dao / 2;
		tdb["apply/attack"] += enhance;
		tdb["apply/defense"] += enhance;
	}

	return 1;
}
