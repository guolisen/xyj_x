// by firefox 11/21/2009

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include <xyj_x.h>

#define MEET_ZIXIA		"meet_zixia"

//HIM"��Լ��������Ǯ��أ���ͷ�������һ���������ݲ�������",

void create()
{
	set_name("����ʮ��", ({ "chun sanshiniang", "chun", "sanshiniang" }));
	set("gender", "Ů��" );
	set("age", 23);
	set("title", "�һ�����");

	set("per", 21);
	set("str", 10);
	set("con", 200);
	set("spi", 200);
	set("cps", 60);

	create_family("��˿��", 2, "����");

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
	//RACE_D->set(_this, "spider", "�ڹѸ�", 5);


}

void die()
{
	if(_env) message_vision(HIM"\n\nֻ��$N������˿����ͬ����һ��Ʈ�ߡ�\n\n"NOR, _this);
	destruct(_this);
}

/*****************************������ͽ*****************************/

void attempt_apprentice(object ob)
{
	if(ob->query_temp(MEET_ZIXIA) < 6
		&& ob->query("family/family_name") != "��˿��") 
	{
		command("say ����������������㡣");
		return;
	}
	command("say �ã��ӽ�����ú��ź��������...�����㣡");
	command("recruit " + ob->query("id") );
}

int recruit_apprentice(object ob)
{
	if(::recruit_apprentice(ob)) ob->set("class", "yaomo");
}
