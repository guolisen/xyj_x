// by firefox 11/21/2009

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIR"������"NOR, ({ "jingu zhou" }) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "ƪ");
		set("long", "�����䣬�ֻ������������ԡ���ײ����ͨ������ħ��ֻ�����õ�������һ��ܽ�������������\n");
		set("material", "paper");       
	}
	setup();
}

void init()
{
	if (this_player() -> query("family/family_name") != "�Ϻ�����ɽ" ) {
		remove_call_out("free_jingu");
		call_out("free_jingu", 120, this_object(), this_player()); 
	}

	::init();
}

int remove()
{
	object env = environment(this_object());

	if (env && userp(env)) {
		call_out("new_one", 2, env); 
		if(env) env->command("xixi");
	}
	return 0;
}

void new_one(object env)
{
	if(env) env->command("hi");
}