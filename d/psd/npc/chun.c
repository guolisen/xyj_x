// by firefox 11/21/2009

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include <xyj_x.h>

#define MEET_ZIXIA		"meet_zixia"

//HIM"隐约传来『金钱落地，人头不保，桃花过处，寸草不生！』",

void create()
{
	set_name("春三十娘", ({ "chun sanshiniang", "chun", "sanshiniang" }));
	set("gender", "女性" );
	set("age", 23);
	set("title", "桃花娘子");

	set("per", 21);
	set("str", 10);
	set("con", 200);
	set("spi", 200);
	set("cps", 60);

	create_family("盘丝洞", 2, "弟子");

	set("combat_exp", 1000*K);
	set("daoxing", 1500*K);

	SKI->set_list(_this, ({
		({ "literate",		50, }),
		({ "ziqing-sword",	140,	"sword",	140,	"parry",	140,	"dodge",	140 }),
		({ "pansi-dafa",	160,	"spells",	160 }),
		({ "huntian-qigong",140,	"force",	140 }), })
	);

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: cast_spell, "love" :),
		(: cast_spell, "pansi" :),
		(: cast_spell, "yihun" :),
	}) );

	HP->to_max(_this);

	setup();

	carry_object("/d/obj/cloth/nichang")->wear();
	carry_object("/d/obj/cloth/yuanxiang")->wear();
	carry_object("/d/obj/weapon/sword/qingfeng")->wield();

	//FABAO_D->carry(_this, "poison-armor")->wear();
	//RACE_D->set(_this, "spider", "黑寡妇", 5);


}

void die()
{
	if(_env) message_vision(HIM"\n\n只见$N口中吐丝，如同风筝一般飘走。\n\n"NOR, _this);
	destruct(_this);
}

/*****************************开门收徒*****************************/

void attempt_apprentice(object ob)
{
	if(ob->query_temp(MEET_ZIXIA) < 6
		&& ob->query("family/family_name") != "盘丝洞") 
	{
		command("say 滚！否则老娘吃了你。");
		return;
	}
	command("say 好，从今往后好好伺候老娘，否则...吃了你！");
	command("recruit " + ob->query("id") );
}

int recruit_apprentice(object ob)
{
	if(::recruit_apprentice(ob)) ob->set("class", "yaomo");
}
