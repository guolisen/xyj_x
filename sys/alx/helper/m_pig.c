// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

string* _str_tab = ({
	"曾经有人说对盘丝洞很有感觉，我不以为然。",
	"直到我加入他，才感慨万千：人世间最强的门派莫过于此。",
	"如果上天再派给我一个不可战胜的敌人，我会对他说三个字：我恶心你。",
	"如果一定要给这种恶心加一个期限，保守估计他也要吐半年。",
});

void on_init(object me, object who)
{
	if(!random(10)) {
		foreach(string str in _str_tab)
			me->command("say " + str);
	}
}

void create()
{
	set_name("猪八戒", ({"zhu bajie", "zhu", "bajie", "pig"}));
	set("gender", "男性" );
	set("age", 33);
	set("long", "\n他就是著名的天蓬元帅。\n");
	set("title", HIM"六蹄猪魔"NOR);

	set("per", 1);
	set("str", 50);	
	
	SKI->set_list2(_this, 
		({
			({ "literate" }),
			
			({ "yinfeng-zhua",		"unarmed" }), 	
			({ "dragonstep",		"dodge" }),
			
			({ "dragonforce",		"force" }),
			({ "seashentong",		"spells" }),

			({ "skyriver-rake",		"rake",		"parry" }),
		}),
		1
	);
	
	set_events(
		([
			"born"		: HIW"草丛中一声哈欠声，$N揉着眼睛走了出来",
			"leave"		: HIW"$N拿出一架"HIG"超时空猪槽子"HIW"，大喝一声『烂吃』！\n"
							+ "$NOOXX了一阵，就OOS了。",
			"init"		: (: on_init :),
	
			"cmds"		: ({ "perform 200", "perform casts", "perform performs" }),
		])
	);

	setup();

	carry_object(__DIR__"obj/p_cloth")->wear();
	carry_object(__DIR__"obj/p_dagger")->wield();
	carry_object("/d/kaifeng/obj/jiuchipa")->wield();
}

