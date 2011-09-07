// by firefox 03/21/2009

inherit NPC;
inherit F_MASTER;

#include <xyj_x.h>
#include <ansi.h>

#define MEET_ZIXIA		"meet_zixia"

void create()
{
	set_name("白晶晶", ({ "bai jingjing", "bai", "jingjing" }));
	set("title", "白骨洞主");
	set("gender", "女性" );
	set("age", 21);

	set("per", 22);
	set("str", 10);
	set("con", 200);
	set("spi", 200);
	set("cps", 60);

	create_family("盘丝洞", 2, "弟子");

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
        "白晶晶望着手里的玉佩，仿佛有无尽的心事。\n",
	}));

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: cast_spell, "fire" :),
	}) );

	setup();

	carry_object("/d/obj/cloth/nichang")->wear();
	carry_object("/d/obj/cloth/yuanxiang")->wear();
	carry_object(__DIR__"equ/yupei")->wear();
	
	//FABAO_D->carry(_this, "bind-whip", "龙骨鞭")->wield();
	//RACE_D->set(_this, "corpse", "白骨精", 5);

}

void die()
{
	if(_env) message_vision(HIW"\n\n$N化作一堆枯骨，散落尘埃。\n\n"NOR, _this);
	destruct(_this);
}

/*****************************开门收徒*****************************/
void attempt_apprentice(object ob)
{
	if(ob->query_temp(MEET_ZIXIA) < 6 
		&& ob->query("family/family_name") != "盘丝洞") 
	{
		command("shake");
		command("say 未经大仙许可，不敢擅自收徒。");
		return;
	}

	if(ob->query("gender") == "男性" && ob->query_per() < 20) {
		command("say 像谁不好，偏偏像猴子。");
		command("sigh");
	}
	command("recruit " + ob->query("id") );
}

int recruit_apprentice(object ob)
{
	if(::recruit_apprentice(ob)) ob->set("class", "yaomo");
}


/*****************************尸变狂暴*****************************/

//尸变是真身，同时狂暴，自动攻击活的人型生物
/*
int _index = 0;

mixed* _tab = ({
	({ "", "", "白骨洞主", }),
	({ HIW, NOR, "尸变白骨精", }),
});
//改变名字
private void change_name()
{
	string c1 = _tab[_index][0];
	string c2 = _tab[_index][1];
	set_name(c1 + "白晶晶" + c2, ({ "bai jingjing", "bai", "jingjing" }));
}

void init()
{	
	object me = this_object();
	object who = this_player();
	object weapon = who->query_temp("weapon");

	string time = CHINESE_D->chinese_date(time());
	_index = (NATURE_D->query_current_day_phase() >= 6)	//月圆之夜
		&& (strsrch(time, "二十五日") >= 0);
	change_name();

	if(_index) {
		if(weapon) weapon->unequip();
		message_vision("$N满头白发，眼似红灯，舞动白森森的利爪，扑向$n！\n", me, who);
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
			message_vision("$N慌忙吻住$n，阳气慢慢过给$n，红灯般的眼睛黯淡了下来。\n", who, target);
			who->start_busy(5);
			return 1;
		}
	}
	return 0;
}
*/