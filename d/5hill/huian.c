
inherit NPC;

void create()
{
	set_name("�ݰ�����", ({ "huian xingzhe", "huian", "xingzhe" }));
	set("title", "������ͽ");   
	set("long", @LONG
��������̫��ľ�棬�Ϻ�������ͽ�ܻݰ����ߡ�
LONG);
	set("gender", "����");
	set("age", 25);
	set("attitude", "peaceful");
	set("rank_info/self", "ƶɮ");
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
		"�": (: ask_for_partner :),
		]) );
*/
	create_family("�Ϻ�����ɽ", 2, "����");

	setup();
// 	carry_object("/obj/money/thousand-cash");
 	carry_object("/obj/money/gold");
	carry_object("/d/nanhai/obj/sengpao")->wear();
	carry_object("/d/nanhai/obj/budd_staff")->wield();
}
