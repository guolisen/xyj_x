// by firefox 11/21/2009

#include <ansi.h>
#include <xyj_x.h>

inherit ITEM;
inherit F_LOADABLE;

void create()
{
	seteuid(getuid());
	set_name(HIY"���ɱ���"NOR, ({ "test pearl", "pearl" }) );
	set("long", "һ�Ź�â����ı��飬����(setmp)�����Ժ��������ɼ��ܡ�\n");
	set("unit", "Ƭ" );
	set("changed", 1);
}

void init()
{
	if(wizardp(this_player())) {
		add_action("do_setmp", "setmp");
		add_action("do_setsk", "setsk");
		add_action("do_seal", "seal");
		add_action("do_test_kill", "test_kill");
		add_action("do_sg", "sg");

		add_action("do_alx", "alx");

		add_action("do_add_prop", "add_prop");
		add_action("do_set_prop", "set_prop");
	}
}

int do_setmp(string arg)
{
	string id;
	string mp;
	int level;
	
	if(arg && sscanf(arg, "%s %s %d", id, mp, level) == 3) {
		object who = present(id, environment(this_player()));
		string family = FAMILY->id_to_name(mp);
		int exp = level * level / 3 * level;

		if(!who) return notify_fail("˭��\n");
		if(!family) return notify_fail("ʲô���ɣ�\n");
		if(level < 1) return notify_fail("���ټ���\n");

		who->create_family(family, 4, "����");

		FAMILY->quick_setup(who, family, level);

	} else {
		return notify_fail("ָ���ʽ��setmp ĳ�� ���ɼ�д ���ܵȼ�\n");
	}
	
	return 1;
}

int do_setsk(string arg)
{
	string id;
	string skill;
	int level;
	
	if(arg && sscanf(arg, "%s %s %d", id, skill, level) == 3) {
		object who = present(id, environment(this_player()));
		if(!who) return notify_fail("˭��\n");
		who->set_skill(skill, level);
	} else {
		return notify_fail("ָ���ʽ��setmp ĳ�� ���� �ȼ�\n");
	}
	
	return 1;
}

int do_seal(string arg)
{
	object kuang = new("/d/obj/misc/kuang");

	for(int i = 0; i < 10; ++i) {
		object bag = new("/d/obj/misc/bag");
		for(int j = 0; j < 10; ++j) {
			new("/d/jjf/obj/escape_seal")->move(bag);
		}
		bag->move(kuang);
	}
	kuang->move(this_player());
	return 1;
}

int do_test_kill(string arg)
{
	object who = arg ? find_player(arg) : 0;

	if(who) {
		BUFF->add(who, ([
			"id"		: "test_kill",
			"name"		: HIG"��������"NOR,
			"comment"	: "�������������",
			"duration"	: 0,
			"interval"	: 20,
			"timer_act"	: function(mapping buff) {
				object me = buff["me"];
				me->delete("mieyao/time_start");
				return 1;
			},
		]));		
	}
	return 1;
}


int do_sg(string arg)
{
	return 1;
}


int do_alx(string arg)
{
	if(arg == "start") ALX->start();
	if(arg == "stop") ALX->stop();
	return 1;
}

int do_add_prop(string arg)
{
	string id;
	string prop;
	int n;

	if(arg && sscanf(arg, "%s %s %d", id, prop, n) == 3) {
		object who = find_player(id);
		who->add(prop, n);
	}
	return 1;
}

int do_set_prop(string arg)
{
	string id;
	string prop;
	int n;

	if(arg && sscanf(arg, "%s %s %d", id, prop, n) == 3) {
		object who = find_player(id);
		who->set(prop, n);
	}
	return 1;
}
