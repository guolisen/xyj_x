// by firefox 11/21/2009
#include <ansi.h>
#include <weapon.h>

inherit BLADE;

void create()
{
	set_name(RED "双" NOR + HIB "色" NOR + HIW "冰刀" NOR, ({"ice blade", "blade", "dao"}));
	set_weight(5000);

	if( clonep(this_object()) ) {
		set_default_object(__FILE__);
	} else {
		set("unit", "把");
		set("long", "一把晶莹透明的弯刀，以大雪山中千年不化的寒冰制成。颜色变幻不停，象红又象蓝。\n");
		set("value", 8000);
		set("material", "ice");
		set("wield_msg", "$N「唰」地一声抽出一把$n握在手中，眼中射出一道寒意！\n");
		set("unwield_msg", "$N将手中的$n插入腰间，嘴里轻轻地舒了口气。\n");
	}
	init_blade(60);
	setup();
}

void init()
{
	remove_call_out("melt");
	call_out("melt", 40 + random(40));
}

void melt()
{
	object me = this_object();
	object env;

	if(!me) return;
	env = environment(me);
	if(env->is_character()) {
		if(env->query_skill("ningxie-force", 1) < 50 ) {
			message_vision("$N觉得身上凉凉的，湿湿的，原来是冰刀化了。\n", env);
			env->apply_condition("double_ice_poison", 10);
			destruct(me);
		}
	}
	else if(env->query("outdoors") != "xueshan") {
		tell_object(env, "冰刀终于化成了一滩水，流得到处都是。\n");
		destruct(me);
	}
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int diff;

	if( damage_bonus < 0 ) return 0;
	diff = me->query("force_factor") - victim->query("force_factor")/2;
	if(diff > 10) {
		victim->apply_condition("double_ice_poison", 
			1 + random(diff) + (int)victim->query_condition("double_ice_poison"));
		message_vision("$N身子一颤，中了刀上的寒毒！\n", victim);
	}
	else 
		message_vision("$N觉得一阵寒意袭来，差点中了刀上的寒毒！\n", victim);
}
