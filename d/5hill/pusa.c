
inherit NPC;

void create()
{
	set_name("��������", ({ "guanyin pusa", "guanyin", "pusa" }));
	set("title", "�ȿ���Ѵ�ȴ�");
	set("long", @LONG
��Բ�ĵ£�����������ü��С�£�����˫�ǡ�����������
ޥ�԰����١���������٤ɽ�ϴȱ�������������������
LONG);
	set("gender", "Ů��");
	set("age", 35);
	set("attitude", "peaceful");
	set("rank_info/self", "ƶɮ");
	set("rank_info/respect", "��������");
	set("class", "bonze");
        	set("str",24);
	set("per",100);//means no rong-mao description.
	set("max_kee", 5000);
	set("max_gin", 5000);
	set("max_sen", 5000);
	set("force", 4000);
	set("max_force", 2000);
	set("force_factor", 145);
	set("max_mana", 3000);
	set("mana", 6000);
	set("mana_factor", 150);
	set("combat_exp", 2000000);
	set("daoxing", 10000000);

	set_skill("literate", 150);
	set_skill("spells", 200);
	set_skill("buddhism", 200);
	set_skill("unarmed", 150);
	set_skill("jienan-zhi", 150);
	set_skill("dodge", 180);
	set_skill("lotusmove", 180);
	set_skill("parry", 180);
	set_skill("force", 180);
	set_skill("lotusforce", 180);
	set_skill("staff", 180);
	set_skill("lunhui-zhang", 180);
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: cast_spell, "bighammer" :),
	}) );
	//hehe, since guanyin was killed several times
	//let's use cast bighammer to protect her...weiqi:)
	create_family("�Ϻ�����ɽ", 1, "����");

	setup();
	carry_object("/d/nanhai/obj/jiasha")->wear();
	carry_object("/d/nanhai/obj/nine-ring")->wield();
}

void die()
{
	if( environment() ) {
		message("sound", "\n\n��������ҡͷ̾�����������ϣ�����ħ�ϣ����伲�࣬���˶�֮��\n\n", environment());
		command("sigh");
		message("sound", "\n�������������ƣ��ǲ�������������ȥ�ˡ�����\n\n", environment());
	}
	destruct(this_object());
}

void unconcious()
{
	die();
}

