// by firefox 11/21/2009
// ����������Ѫǹ

#include <weapon.h>
#include <ansi.h>
inherit SPEAR;

string* _names = ({ "��߬����ǹ", "��ˮ��¯ǹ", "�˱�����ǹ" });

string _long = @LONG

ǹ��һ����˴磬��ʮ������ֻƽ�������ɣ��˵��ǽ������������ʮ�㡣
������Ϳɽ�����죬��һ���������𣬹�Ҳ�ư���ǹ���ڶ�������Ϊ��ʮ����
�еľ�ľ��

LONG;

void create()
{
	set_name(HIY + names[random(3)] + NOR, ({"spear"}));
	set_weight(1000);
	if(clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", _long);
		set("material", "iron");
		set("wield_msg","$N�ó�һ��$n���������У�\n");
		set("unwield_msg", "$N�������е�$n��\n");
	}
	init_spear(60);
	setup();
}

//��Ѫ
mixed hit_ob(object me, object victim, int damage_bonus)
{
	//20%������Ѫ
	if(!random(5) && damage_bonus > 0) {
		int damage = damage_bonus;
		victim->receive_damage("kee", damage, me);
		victim->receive_wound("kee", damage, me);

		message_vision("����"HIR"��Ѫ"NOR"��$N��ǹβ��������\n", me);
	}
}

