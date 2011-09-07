
inherit NPC;

void create()
{
	set_name("惠岸行者", ({ "huian xingzhe", "huian", "xingzhe" }));
	set("title", "观音首徒");   
	set("long", @LONG
李天王二太子木叉，南海观音大徒弟惠岸行者。
LONG);
	set("gender", "男性");
	set("age", 25);
	set("attitude", "peaceful");
	set("rank_info/self", "贫僧");
	set("class", "bonze");
	set("max_kee", 1000);
	set("max_gin", 600);
	set("max_sen", 1000);
	set("force", 2000);
	set("max_force", 1000);
	set("force_factor", 75);
	set("max_mana", 1000);
	set("mana", 2000);
	set("mana_factor", 55);
	set("combat_exp", 750000);
	set("daoxing", 1000000);


        set("eff_dx", 150000);
        set("nkgain", 300);

	set_skill("literate", 100);
	set_skill("spells", 120);
	set_skill("buddhism", 120);
	set_skill("unarmed", 100);
	set_skill("jienan-zhi", 100);
	set_skill("dodge", 100);
	set_skill("lotusmove", 100);
	set_skill("parry", 100);
	set_skill("force", 100);
	set_skill("lotusforce", 100);
	set_skill("staff", 120);
	set_skill("lunhui-zhang", 120);
//	set_skill("spear", 80);
//	set_skill("huoyun-qiang", 60);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
	map_skill("spear", "huoyun-qiang");

	set("chat_chance_combat", 40);
	set("chat_msg_combat", ({
		(: cast_spell, "bighammer" :),
		(: cast_spell, "jingang" :)
	}) );
/*
	set("inquiry", ([
		"dadang" : (: ask_for_partner :),
		"partner" : (: ask_for_partner :),
		"搭档": (: ask_for_partner :),
		]) );
*/
	create_family("南海普陀山", 2, "弟子");

	setup();
// 	carry_object("/obj/money/thousand-cash");
 	carry_object("/obj/money/gold");
	carry_object("/d/nanhai/obj/sengpao")->wear();
	carry_object("/d/nanhai/obj/budd_staff")->wield();
}
