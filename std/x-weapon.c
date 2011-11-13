// firefox 2011.11
// �ɱ����

#include <weapon.h>

inherit EQUIP;

static mapping _infos = ([
	"axe"		: ({ EDGED, ({ "chop", "slice", "hack" }) }),
	"blade"		: ({ EDGED, ({ "slash", "slice", "hack", "chop" }) }),
	"dagger"	: ({ EDGED | SECONDARY,	({ "pierce", "thrust" }) }),
	"fork"		: ({ POINTED,	({ "pierce", "thrust" }) }),
	"hammer"	: ({ 0,	({ "bash", "crush", "slam" }) }),
	"mace"		: ({ 0,	({ "impale", "bash", "crush", "slam" }) }),
	"rake"		: ({ EDGED,	({ "rake", "strike", "bash" }) }),
	"spear"		: ({ POINTED, ({ "thrust", "impale", "pierce" }) }),
	"staff"		: ({ LONG,	({ "bash", "crush", "slam", "pierce", "impale" }) }),
	"stick"		: ({ LONG,	({ "bash", "crush", "slam" }) }),
	"swork"		: ({ EDGED,	({ "slash", "slice", "thrust", "pierce" }) }),
	"whip"		: ({ 0,	({ "whip","wave" }) }),
	"mace"		: ({ 0,	({ "impale", "bash", "crush", "slam" }) }),
	"unarmed"	: ({ 0, ({ "bash", "crush", "slam" }) }),

]);

varargs void init_type(string type, int damage, int flag)
{
	mixed* info = _infos[type];

	set("weapon_prop/damage", damage);
	set("flag", flag | info[0]);
	set("skill_type", type);
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", info[1] );
	}
}


void create()
{
	set_name("��ħ��", ({"xiangmo bang", "bang"}));
	set_weight(8000);

	set("unit", "��");
	set("no_sell", 1);
	set("long", "һ�ѵ���ɫ�Ķ̰��������а�����������ͬһ�����߰����ڰ��ϡ�\n");
	set("value", 20000);
	set("material", "steel");
	set("wield_msg", "$N��������һ�����һ��$n�������С�\n");

	init_type("stick", 60);
	setup();
}

void init()
{
	add_action("do_transform", "transform");
}

int do_transform(string arg)
{
	mixed* info = _infos[arg];
	if(!info) return notify_fail("Ҫ���������ʲô��\n");

	init_type(arg, 100, 0);
}