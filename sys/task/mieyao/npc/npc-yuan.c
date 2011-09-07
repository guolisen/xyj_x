// by firefox 04/20/2010

#include <xyj_x.h>

inherit EMPLOYER;

void create()
{
	set_name("袁天罡", ({"yuan tiangang", "yuan"}));
	set("gender", "男性" );
	set("age", 33);
	set("long","

袁天罡是天监台总管，听说他法术高深。
他为人正直仗义，脸上总是一股忧国忧民的神情。

");
	set("int", 30);
	set("per", 25);
	set("combat_exp", 50*K);
	set("daoxing", 800*K);

	// discourage NK yuan.
	set("eff_dx",1000);
	set("nkgain",1);
	set("env/wimpy",100);

	set("title", "天监台正先生");

	set("max_kee", 400);
	set("max_sen", 400);
	set("force", 450);
	set("max_force", 300);
	set("force_factor", 10);
	set("mana", 6000);
	set("max_mana", 3000);
	set("mana_factor", 100);

	SKI->set_list(this_object(), ({
		({ "literate",		50, }),
		({ "sword",			60 }),
		({ "force",			50 }),
		({ "dodge",			50 }),
		({ "changquan",		50,		"unarmed",	60 }),
		({ "baguazhou",		100,	"spells",	100 }), })
	);

	set("chat_msg", ({
		name() + "叹道：生逢乱世，妖魔横行啊！\n",
		name() + "问道：可有谁愿去为大唐灭妖吗？\n",})
	);

	set_task(TASK_GET("mieyao", "mieyao"),
		({"mieyao", "kill", "灭妖", "妖魔"}),
		([
			"task"		: "$N将手中桃木剑向四方一划，对$n说道：\n"
				+ "　　近有%s在%s出没，为害不小，请速去收服！\n",
			"repeat"	: "$N说道：在下不是请您去收服%s吗？\n",
			"cd"		: "$N将手中桃木剑缓缓放下，说：多谢$r,妖魔已经除尽了。\n",
		])
	);

	setup();

	add_money("silver", 5);
	carry_object("/d/obj/cloth/baguapao")->wear();
	carry_object("/d/obj/weapon/sword/taomujian")->wield();
}

int accept_fight(object me)
{
	write("袁天罡凛然道：学武乃是为了强身，不是打打杀杀！\n");
	return 0;
}

int recognize_apprentice(object me)
{
	if((int)me->query("yuan-learn"))
		return 1;
	return notify_fail("袁天罡说道：您太客气了，这怎么敢当？\n");
}

int accept_object(object who,object ob)
{
	if (ob->query("id")=="fan he"){
		if (((string)who->query("family/family_name")=="将军府")){
			who->set("yuan-learn", 1);
			write("袁天罡笑道：将军看起来一表人才，以后定是人前出头之辈！
				袁天罡略为沉思，又道：若将军有何问题，可随时和我商讨，天罡若是知晓，定会答复．\n");
				call_out("destroy", 1, ob);
			return 1;
		}
		if (((string)who->query("family/family_name")!="将军府")){
			command("say 多谢多谢，我正饿着哪！");
			command("give 1 silver to " + who->query("id"));                        
			call_out("destroy", 1, ob);
			return 1;
		}
	}
	else return 0;
}

void destroy(object ob)
{
	destruct(ob);
	return;
}

