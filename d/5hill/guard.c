
inherit NPC;

#include <ansi.h>

void create()
{
	set_name("山神", ({ "shan shen", "shen", "guard" }));
	set("title", "两界山巡山");   

	set("gender", "男性");
	set("age", 25);
	set("attitude", "peaceful");
	set("rank_info/self", "小神");

	set_skill("spells", 100);
	set_skill("taiyi", 100);
	set_skill("force", 100);
	set_skill("zhenyuan-force", 100);
	set_skill("dodge", 100);
	set_skill("baguazhen", 100);
	set_skill("parry", 100);
	set_skill("staff", 100);
	set_skill("fumo-zhang", 100);

	map_skill("spells", "taiyi");	
	map_skill("force", "zhenyuan-force");
	map_skill("dodge", "baguazhen");
	map_skill("parry", "fumo-zhang");
	map_skill("staff", "fumo-zhang");

	set("chat_chance_combat", 40);
	set("chat_msg_combat", ({
		(: cast_spell, "zhenhuo" :),
		(: cast_spell, "zhenhuo" :)
	}) );

	setup();
	carry_object("/d/obj/armor/shoupi")->wear();
	carry_object("/d/obj/weapon/staff/tieguai")->wield();
}

void die()
{
	object me = this_object();
	message_vision(CYN"$N见势不妙，一阵轻烟没入山林中。\n"NOR, me);
	destruct(me);
}

void unconcious()
{
	die();
}


//获取最高技能等级
int max_level(object who)
{
	int n = 0;
	mapping skills = who->query_skills();
	if(!mapp(skills)) return 0;
	foreach(string skill, int level in skills) {
		if(level > n) n = level;
	}
	return n;
}

void copy_status(object ob)
{
	object me = this_object();
	int ratio = 120;

	int max_sen = ob->query("max_sen") * ratio / 100;
	int max_kee = ob->query("max_kee") * ratio / 100;
	int exp = ob->query("combat_exp") * ratio / 100;
	int force = ob->query("max_force") * ratio / 100;
	int mana = ob->query("max_mana") * ratio / 100;
	
	int level = max_level(ob) * ratio / 100;	
	mapping skills = me->query_skills();

	foreach(string k in keys(skills)) {
		me->set_skill(k, level);
	}

	me->set("combat_exp", exp);
	me->set("daoxing", (ob->query("daoxing")*2 + exp) * ratio / 300);
	
	me->set("max_kee", max_kee);
	me->set("max_sen", max_sen);
	me->set("eff_kee", max_kee);
	me->set("eff_sen", max_sen);
	me->set("kee", max_kee);
	me->set("sen", max_sen);

	me->set("max_force", force);
	me->set("max_mana", force);
	me->set("force", force * 2);
	me->set("mana", force * 2);

	me->set("force_factor", level / 2);
	me->set("mana_factor", me->query("max_mana")/20 + 1);
}
