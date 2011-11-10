// firefox 11/10/2011
// 护法

inherit NPC;

#include <xyj_x.h>

void create()
{
	set_name("护法", ({"jiashen"}));
	set("gender","男性");

	set("age",30);
	set("str",30);
	set("per",20);
	set("combat_exp",1000);
	set("daoxing",1000);
        set("attitude", "friendly");
	set_skill("dodge",10);
	set_skill("moshenbu",10);
	map_skill("dodge","moshenbu");

	setup();
}


void call()
{
	if(me->query("mana") < cost)
		return notify_ok("你的法力不够了！\n");

	if(!cd_start(me, "invoke", CD)) 
		return notify_ok("你刚刚分过身，再分身很危险！\n");

	message("vision",
		RED "只听啪！的一声，一团红光爆开，现出一个身穿金甲手执禅杖的金刚。\n\n"
		+ name() + "说道：末将奉法主召唤，特来护法！\n" NOR,
		environment(), this_object() );
}


void invocation(object leader)
{
	object me = this_object();

	set_temp("invoker", leader);
	set_leader(leader);

	foreach(object enemy in leader->query_enemy()) {
		if(enemy && living(enemy)) {
			kill_ob(enemy);
			if(userp(enemy)) enemy->fight_ob(me);
			else {
				enemy->kill_ob(me);
				enemy->kill_ob(leader);
			}
		}
	}
}




void die()
{
	message_vison(query("leave_msg"), this_object());
	destruct(this_object());
}

