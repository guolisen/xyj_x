// firefox 2011.11
// �ɱ����

#include <weapon.h>
#include <ansi.h>

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
	"sword"		: ({ EDGED,	({ "slash", "slice", "thrust", "pierce" }) }),
	"whip"		: ({ 0,	({ "whip","wave" }) }),
	"unarmed"	: ({ 0, ({ "bash", "crush", "slam" }) }),
]);

///��ʼ���ɱ���
varargs void init_type(string type, int damage, int flag)
{
	mixed* info = _infos[type];

	set("weapon_prop/damage", damage);
	set("flag", flag | info[0]);
	set("skill_type", type);
	if(!query("actions")) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", info[1]);
	}
	decrease_dodge("weapon_prop");
}

static mapping _weapons = ([
	"axe"		: ({ "����", ({ "tie fu", "axe" }), "��" }),
	"blade"		: ({ "�ֵ�", ({ "gang dao", "blade" }), "��" }),
	"dagger"	: ({ "ذ��",	({ "bi shou", "dagger" }), "��" }),
	"fork"		: ({ "�ֲ�",	({ "gang cha", "fork" }), "��" }),
	"hammer"	: ({ "����",	({ "tie chui", "hammer", "��" }) }),
	"mace"		: ({ "ͭ�",	({ "tong jian", "mace", "ֻ" }) }),
	"rake"		: ({ "����",	({ "tie pa", "rake" }), "��" }),
	"spear"		: ({ "��ǹ", ({ "tie qiang", "spear" }), "��" }),
	"staff"		: ({ "����",	({ "tie zhang", "staff" }), "��" }),
	"stick"		: ({ "����",	({ "tie gun", "stick" }), "��" }),
	"sword"		: ({ "����",	({ "tie jian", "sword" }), "��" }),
	"whip"		: ({ "Ƥ��",	({ "pi bian","whip" }), "��" }),
	"unarmed"	: ({ "ȭ��",	({ "quan li","knuckles" }), "��" }),
]);

///�����������
int do_transform(string arg)
{
	mixed* info = _infos[arg];
	mixed* arr = _weapons[arg];
	object who = this_player();
	object weapon = who->query_temp("weapon");
	string name;
	
	if(!info) return notify_fail("Ҫ���������ʲô��\n");
	if(weapon != this_object()) return notify_fail("ֻ�ܱ仯����������\n");
	
	name = name();
	unequip();
	
	init_type(arg, 30, 0);
	set_name(arr[0], arr[1]);
	set("unit", arr[2]);

	wield();
	message_vision(CYN"$N��������" + name + "���˿�������" + name() + "��\n"NOR, who);
	who->reset_action();
	return 1;
}

///���
void make_fake(object ob)
{
	int damage = 1 + ob->query("weapon_prop/damage") / 2;

	set_name(ob->query("name"), ob->query_my_id());
	init_type(ob->query("skill_type"), damage, ob->query("flag"));
	set("unit", ob->query("unit"));

	set("no_get", 1);
	set("no_stock", 1);
	set("no_give", 1);
}

void create()
{
	set_name("�ɱ�����", ({"x weapon"}));
	set_weight(1);

	set("unit", "��");

	set("long", "һ�ѿ�������仯�ı�����\n");

	init_type("stick", 60);
	setup();
}

void init()
{
	add_action("do_transform", "transform");
	add_action("do_test", "test");
}

int do_test()
{
	make_fake(this_player()->query_temp("weapon"));
}
