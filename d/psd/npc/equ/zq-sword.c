// by firefox 03/21/2009

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
	set_name(HIM"���ལ"NOR, ({ "ziqing sword", "sword" }) );
	set_weight(400);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 700);
		set("material", "steel");
		set("long", "�������߲��顢�Ż�����Ϊ�Σ����ϳ���˪ѩ���ϵ���˪��\n");
		set("wield_msg", "$N���$n�������У�������ˡ�\n");
		set("unwield_msg", "$N��$n���뽣�ʣ��⻪���ա�\n");
	}
	init_sword(175);
	setup();
}


int wield()
{
	object owner = environment();
	
	
	if(owner){
		string id = owner->query("id");
		if(wizardp(owner) || id == "zi xia" || id == "qing xia")
			return ::wield();
		if(owner->is_character())
			message_vision("$Nʹ�����̵ľ�Ҳ�޷��ӽ����аγ�$n��\n", owner, this_object());
	}
	return 0;
}


	
