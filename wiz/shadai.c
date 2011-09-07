
inherit NPC;

#include <ansi.h>

string* _props = ({
	"combat_exp", "daoxing",
	
	"kee", "max_kee", "eff_kee",
	"sen", "max_sen", "eff_sen",
			
	"force", "max_force", "force_factor",
	"mana", "max_mana", "mana_factor",
	
	"str", "int", "spi", "con",
	"kar", "cps", "per", "cor",
	"bellicosity",
});

int copy_all(object who, int radio)
{
	//��������
	object w1;
	while(w1 = this_object()->query_temp("weapon")) {
		w1->unequip();
		destruct(w1);
	}
	if(w1 = who->query_temp("weapon")) {
		if((w1 = new(base_name(w1))) && w1->move(this_object()))
			w1->wield();
	}
	//���Ƽ���
	foreach(string k, int v in who->query_skills())
		set_skill(k, v * radio / 100);

	foreach(string k, string v in who->query_skill_map())
		map_skill(k, v);

	//��������
	foreach(string prop in _props)
		set(prop, who->query(prop) * radio / 100);
	
	//���ƻ��׵�
	set_temp("apply", ([]) + who->query_temp("apply"));
		
}


void create()
{
	set_name("ɳ��", ({ "shadai", "dai" }));
	set("long", @LONG

һ�������ɳ��������ָ�
    say n     nȡֵ[1-1000] ������İٷֱ�
    stop      ֹͣս��

LONG
);
	set("title", HIY"����"NOR);
	set("gender", "����");
	set("age", 18);
	set("per", 120);

	set_temp("no_move", 1);

	setup();
}

void init()
{
	::init();
	add_action("do_say", "say");
	add_action("do_stop", "stop");
	add_action("do_full", "full");
}

int do_say(string arg)
{
	int pct = to_int(arg);
	if(pct < 1 || pct > 1000) return 0;

	copy_all(this_player(), pct);
	tell_room(environment(), "����Ϊ:" + pct + "%��\n");
	
	return 1;
}

int do_stop(string arg)
{
	this_object()->remove_all_killer();
	this_player()->remove_all_killer();
	tell_room(environment(), "ֹͣս����\n");
	return 1;
}

mapping _tab = ([ "kee" : "��Ѫ", "sen" : "����" ]);

int full(object who)
{
	who->set("eff_kee", who->query("max_kee"));
	who->set("kee", who->query("max_kee"));
	who->set("eff_sen", who->query("max_sen"));
	who->set("sen", who->query("max_sen"));
	who->set("force", who->query("max_force") * 2);
	who->set("mana", who->query("max_mana") * 2);
	return 1;
}

int do_full(string arg)
{
	if(arg) return 0;
	write("OK.\n");
	return full(this_player());
}


varargs int receive_wound(string type, int damage, object who)
{
	tell_room(environment(), HIY"�ܵ�" + _tab[type] + "Ӳ�˺���" + damage + "��\n"NOR);
	return ::receive_wound(type, damage, who);
}

varargs int receive_damage(string type, int damage, object who)
{
	tell_room(environment(), HIG"�ܵ�" + _tab[type] + "���˺���" + damage + "��\n"NOR);
	return ::receive_damage(type, damage, who);
}

void die()
{
	full(this_object());
}

void unconcious()
{
	die();
}

