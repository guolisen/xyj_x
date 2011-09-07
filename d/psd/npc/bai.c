// by firefox 03/21/2009

inherit NPC;
inherit F_MASTER;

#include <xyj_x.h>
#include <ansi.h>

#define MEET_ZIXIA		"meet_zixia"

void create()
{
	set_name("�׾���", ({ "bai jingjing", "bai", "jingjing" }));
	set("title", "�׹Ƕ���");
	set("gender", "Ů��" );
	set("age", 21);

	set("per", 22);
	set("str", 10);
	set("con", 200);
	set("spi", 200);
	set("cps", 60);

	create_family("��˿��", 2, "����");

	set("combat_exp", 1000*K);
	set("daoxing", 1500*K);

	SKI->set_list(this_object(), ({
		({ "literate",		80, }),
		({ "baigu-whip",	160,	"whip",		160,	"parry",	120,	"dodge",	120 }),
		({ "ziqing-sword",	120,	"sword",	120 }),
		({ "pansi-dafa",	140,	"spells",	140 }),
		({ "tonsillit",		120,	"force",	140 }),
		({ "yinfeng-zhua",	120,	"unarmed",	120 }), })
	);

	set("chat_chance", 1);
	set("chat_msg", ({
        "�׾���������������壬�·����޾������¡�\n",
	}));

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: cast_spell, "fire" :),
	}) );

	setup();

	carry_object("/d/obj/cloth/nichang")->wear();
	carry_object("/d/obj/cloth/yuanxiang")->wear();
	carry_object(__DIR__"equ/yupei")->wear();
	
	//FABAO_D->carry(_this, "bind-whip", "���Ǳ�")->wield();
	//RACE_D->set(_this, "corpse", "�׹Ǿ�", 5);

}

void die()
{
	if(_env) message_vision(HIW"\n\n$N����һ�ѿݹǣ�ɢ�䳾����\n\n"NOR, _this);
	destruct(_this);
}

/*****************************������ͽ*****************************/
void attempt_apprentice(object ob)
{
	if(ob->query_temp(MEET_ZIXIA) < 6 
		&& ob->query("family/family_name") != "��˿��") 
	{
		command("shake");
		command("say δ��������ɣ�����������ͽ��");
		return;
	}

	if(ob->query("gender") == "����" && ob->query_per() < 20) {
		command("say ��˭���ã�ƫƫ����ӡ�");
		command("sigh");
	}
	command("recruit " + ob->query("id") );
}

int recruit_apprentice(object ob)
{
	if(::recruit_apprentice(ob)) ob->set("class", "yaomo");
}


/*****************************ʬ���*****************************/

//ʬ��������ͬʱ�񱩣��Զ����������������
/*
int _index = 0;

mixed* _tab = ({
	({ "", "", "�׹Ƕ���", }),
	({ HIW, NOR, "ʬ��׹Ǿ�", }),
});
//�ı�����
private void change_name()
{
	string c1 = _tab[_index][0];
	string c2 = _tab[_index][1];
	set_name(c1 + "�׾���" + c2, ({ "bai jingjing", "bai", "jingjing" }));
}

void init()
{	
	object me = this_object();
	object who = this_player();
	object weapon = who->query_temp("weapon");

	string time = CHINESE_D->chinese_date(time());
	_index = (NATURE_D->query_current_day_phase() >= 6)	//��Բ֮ҹ
		&& (strsrch(time, "��ʮ����") >= 0);
	change_name();

	if(_index) {
		if(weapon) weapon->unequip();
		message_vision("$N��ͷ�׷������ƺ�ƣ��趯��ɭɭ����צ������$n��\n", me, who);
		me->kill_ob(who);		
	} else {
		if(!weapon) command("wield all");
	}

	::init();

	add_action("do_kiss", "kiss");

}

int do_kiss(string arg)
{
	if(arg) {
		object target = present(arg, environment());
		if(target == this_object()) {
			object who = this_player();
			target->remove_all_killer();
			who->remove_all_killer();
			message_vision("$N��æ��ס$n��������������$n����ư���۾�������������\n", who, target);
			who->start_busy(5);
			return 1;
		}
	}
	return 0;
}
*/