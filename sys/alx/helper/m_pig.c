// by firefox 11/21/2009

#include <xyj_x.h>
#include <ansi.h>

inherit __DIR__"m_base";

string* _str_tab = ({
	"��������˵����˿�����ио����Ҳ���ΪȻ��",
	"ֱ���Ҽ��������Ÿп���ǧ����������ǿ������Ī���ڴˡ�",
	"����������ɸ���һ������սʤ�ĵ��ˣ��һ����˵�����֣��Ҷ����㡣",
	"���һ��Ҫ�����ֶ��ļ�һ�����ޣ����ع�����ҲҪ�°��ꡣ",
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
	set_name("��˽�", ({"zhu bajie", "zhu", "bajie", "pig"}));
	set("gender", "����" );
	set("age", 33);
	set("long", "\n����������������Ԫ˧��\n");
	set("title", HIM"������ħ"NOR);

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
			"born"		: HIW"�ݴ���һ����Ƿ����$N�����۾����˳���",
			"leave"		: HIW"$N�ó�һ��"HIG"��ʱ�������"HIW"�����һ�����óԡ���\n"
							+ "$NOOXX��һ�󣬾�OOS�ˡ�",
			"init"		: (: on_init :),
	
			"cmds"		: ({ "perform 200", "perform casts", "perform performs" }),
		])
	);

	setup();

	carry_object(__DIR__"obj/p_cloth")->wear();
	carry_object(__DIR__"obj/p_dagger")->wield();
	carry_object("/d/kaifeng/obj/jiuchipa")->wield();
}

