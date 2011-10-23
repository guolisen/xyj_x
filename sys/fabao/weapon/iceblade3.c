// by firefox 11/21/2009
#include <ansi.h>
#include <weapon.h>

inherit BLADE;

void create()
{
	set_name(RED "˫" NOR + HIB "ɫ" NOR + HIW "����" NOR, ({"ice blade", "blade", "dao"}));
	set_weight(5000);

	if( clonep(this_object()) ) {
		set_default_object(__FILE__);
	} else {
		set("unit", "��");
		set("long", "һ�Ѿ�Ө͸�����䵶���Դ�ѩɽ��ǧ�겻���ĺ����Ƴɡ���ɫ��ò�ͣ�������������\n");
		set("value", 8000);
		set("material", "ice");
		set("wield_msg", "$N��ৡ���һ�����һ��$n�������У��������һ�����⣡\n");
		set("unwield_msg", "$N�����е�$n�������䣬������������˿�����\n");
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
			message_vision("$N�������������ģ�ʪʪ�ģ�ԭ���Ǳ������ˡ�\n", env);
			env->apply_condition("double_ice_poison", 10);
			destruct(me);
		}
	}
	else if(env->query("outdoors") != "xueshan") {
		tell_object(env, "�������ڻ�����һ̲ˮ�����õ������ǡ�\n");
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
		message_vision("$N����һ�������˵��ϵĺ�����\n", victim);
	}
	else 
		message_vision("$N����һ����Ϯ����������˵��ϵĺ�����\n", victim);
}
